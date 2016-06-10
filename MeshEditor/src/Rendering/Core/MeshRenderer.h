#pragma once

#include "Rendering\Model\Mesh.h"
#include <vector>
#include "Dependencies\glew\include\glew.h"
#include "Dependencies\glm\glm.hpp"

#define NB_BUFFER 5

namespace Rendering
{
	namespace Core
	{
		enum RenderMode {
			MESH = 1,
			WIREFRAME = 1 << 2,
			VERTICES = 1 << 3,
			FACES_NORMALS = 1 << 4,
			VERTICES_NORMALS = 1 << 5
		};

		enum BufferId {
			BUF_VERTICES = 0,
			BUF_FACES = 1,
			BUF_NORMALS = 2,
			BUF_FACES_NORMALS = 3,
			BUF_VERTICES_NORMALS = 4
		};

		enum LightType {
			AMBIANT = 0,
			POINT_LIGHT = 1,
			DIRECTIONNAL = 2,
			SPOT_LIGHT = 3,
			SILOUHETTE = 4
		};

		class MeshRenderer
		{
		private:
			Model::Mesh* mesh; // Mesh in half-edge structure

			// Mesh as vertices + faces + normals arrays for better performances
			// Reloaded when the mesh is modified
			std::vector<GLfloat> vertices;
			std::vector<GLuint> faces;
			std::vector<GLfloat> normals;
			std::vector<GLfloat> verticesNormals;
			std::vector<GLfloat> facesNormals;

			GLuint buffers[NB_BUFFER]; // Buffers for each previous arrays
			bool verticesNormalsUpdated;
			bool facesNormalsUpdated;

			glm::vec3 cameraEye; // Position of the camera
			glm::vec3 cameraUp; // Camera orientation
			glm::vec3 cameraForward; // Camera direction

			// Viewer parameters
			int viewportWidth;
			int viewportHeight;
			float fovy;
			float zNear;
			float zFar;
			RenderMode renderMode;

			// Light parameters
			LightType lightType;
			glm::vec4 lightColor;
			glm::vec3 lightPosition;
			glm::vec3 lightDirection;
			float lightAngle;

			GLuint program; // Shader program

			// Shaders variables
			GLuint projectionMatrixLoc;
			GLuint viewMatrixLoc;
			GLuint meshColorLoc;
			GLuint lightTypeLoc;
			GLuint lightColorLoc;
			GLuint lightPositionLoc;
			GLuint lightDirectionLoc;
			GLuint lightAngleLoc;

			// Display functions
			void DisplayMesh();
			void DisplayWireframe();
			void DisplayVertices();
			void DisplayFacesNormals();
			void DisplayVerticesNormals();

			void DrawMesh(unsigned int drawMode, GLuint program, glm::vec4 color, LightType lightType);
			void DrawNormals(BufferId buffer, GLuint program, glm::vec4 color, LightType lightType);

			void UpdateFacesNormals();
			void UpdateVerticesNormals();
			void GenerateFacesNormals();
			void GenerateVerticesNormals();

		public:
			MeshRenderer(int viewportWidth, int viewportHeight, Model::Mesh* mesh = NULL);
			~MeshRenderer();

			void Init(); // Initialize opengl context

			void SetMesh(Model::Mesh* mesh);
			Model::Mesh* GetMesh();

			// Must be called whenever the mesh connectivity has changed (new or removes vertices/edge/face)
			// Update vertices, faces and normals arrays
			void UpdateMeshConnectivity();

			// UpdateMeshGeomtry() methods must be called whenever the mesh geometry has changed (i.e. some vertices' positions have changed)
			// Update all vertices
			void UpdateMeshGeometry();
			// Update a subset of all vertices
			void UpdateMeshGeometry(std::vector<Rendering::Model::Vertex*> vertices);
			// Update a single vertex
			void UpdateMeshGeometry(Rendering::Model::Vertex* vertex);

			// Display the model by sending the vertices, faces and normals arrays to the graphic card
			void Display();

			void SetRenderMode(RenderMode renderMode);

			void SetLightType(LightType lightType);
			void SetLightColor(glm::vec4 color);
			void SetLightPosition(glm::vec3 position);
			void SetLightDirection(glm::vec3 direction);
			void SetLightAngle(float angle);

			void SetViewPort(int viewportWidth, int viewportHeight);
			void Rotate(float x, float y); // Rotate the model around the x axis by x degrees and around the y axis by y degrees
			void Translate(float x, float y);
			void Zoom(float value);
		};
	}
}
