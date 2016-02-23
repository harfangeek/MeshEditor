#pragma once

#include "Model\Mesh.h"
#include <vector>
#include "Dependencies\glew\glew.h"
#include "Dependencies\glm\glm.hpp"

#define NB_BUFFER 5

namespace Core
{
	enum RenderMode {
		MESH = 1,
		WIREFRAME = 1 << 2,
		VERTICES = 1 << 3,
		FACES_NORMALS = 1 << 4,
		VERTICES_NORMALS = 1 << 5,
		SILOUHETTE = 1 << 6
	};

	enum BufferId {
		BUF_VERTICES = 0,
		BUF_FACES = 1,
		BUF_NORMALS = 2,
		BUF_FACES_NORMALS = 3,
		BUF_VERTICES_NORMALS = 4
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

			GLuint program; // Shader program
			
			// Shaders variables
			GLuint projection_matrix_loc;
			GLuint view_matrix_loc;
			GLuint color_loc;

			// Display functions
			void DisplayMesh();
			void DisplayWireframe();
			void DisplayVertices();
			void DisplayFacesNormals();
			void DisplayVerticesNormals();
			void DisplaySilouhette();
			
			void DrawMesh(unsigned int drawMode, GLuint program, glm::vec4 color);
			void DrawNormals(BufferId buffer, GLuint program, glm::vec4 color);

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
			
			// Must be called whenever the mesh structure has changed.
			// Update vertices, faces and normals arrays
			void UpdateMesh(); 

			// Display the model by sending the vertices, faces and normals arrays to the graphic card
			void Display();

			void SetRenderMode(RenderMode renderMode);
			void SetViewPort(int viewportWidth, int viewportHeight);

			// Rotate the model around the x axis by x degrees and around the y axis by y degrees
			void Rotate(float x, float y);
			void Translate(float x, float y);
			void Zoom(float value);
	};
}
