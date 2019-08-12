#pragma once

#include <vector>
#include "GL/gl3w.h"
#include "GLM/glm.hpp"

#define NB_VAO 4
#define NB_VBO 7

namespace Rendering
{
	class Mesh;
	class Vertex;
	
	enum RenderMode {
		MESH = 1,
		WIREFRAME = 1 << 2,
		VERTICES = 1 << 3,
		FACES_NORMALS = 1 << 4,
		VERTICES_NORMALS = 1 << 5
	};

	enum MaterialType {
		MATERIAL_LIGHT = 0,
		MATERIAL_NO_LIGHT
	};

	enum VAO {
		VAO_MESH = 0,
		VAO_VERTICES,
		VAO_FACES_NORMALS,
		VAO_VERTICES_NORMALS
	};

	enum VBO {
		VBO_VERTICES = 0,
		VBO_FACES = 1,
		VBO_NORMALS = 2,
		VBO_FACES_NORMALS = 3,
		VBO_VERTICES_NORMALS = 4,
		VBO_VERTICES_SELECTION = 5,
		VBO_EDGES_SELECTION = 6
	};

	class MeshRenderer
	{
	private:
		Mesh* mesh; // Mesh in half-edge structure

		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

		// Mesh as vertices + faces + normals arrays for better performances
		// Reloaded when the mesh is modified
		std::vector<GLfloat> vertices;
		std::vector<GLuint> faces;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> verticesNormals;
		std::vector<GLfloat> facesNormals;
		std::vector<GLint> verticesSelection;
		std::vector<GLint> edgesSelection;

		// VBOs and VAOs
		GLuint vaoIds[NB_VAO];
		GLuint vboIds[NB_VBO];

		bool verticesNormalsUpdated;
		bool facesNormalsUpdated;

		// Shaders variables		
		GLuint modelMatrixLoc;
		GLuint meshColorLoc;
		GLuint materialTypeLoc;

		// Rendering parameters		
		RenderMode renderMode;		

		void Clean();

		void InitVAOMesh();
		void InitVAOVertices();
		void InitVAOFacesNormals();
		void InitVAOVerticesNormals();

		void Draw(GLuint polygonMode, GLuint drawMode, bool elements, VAO vaoId, size_t size, const glm::vec4& color, const MaterialType materialType);

		void UpdateFacesNormals();
		void UpdateVerticesNormals();
		void GenerateFacesNormals();
		void GenerateVerticesNormals();

	public:
		MeshRenderer(Mesh* mesh = NULL);
		~MeshRenderer();

		void Init(GLuint program);	

		void SetMesh(Mesh* mesh);
		Mesh* GetMesh();

		void SetTranslation(glm::vec3 translation);
		glm::vec3 GetTranslation();
		void SetRotation(glm::vec3 rotation);
		glm::vec3 GetRotation();
		void SetScale(glm::vec3 scale);
		glm::vec3 GetScale();

		// Must be called whenever the mesh connectivity has changed (new or removes vertices/edge/face)
		// Update vertices, faces and normals arrays
		void UpdateMeshConnectivity();

		// UpdateMeshGeomtry() methods must be called whenever the mesh geometry has changed (i.e. some vertices' positions have changed)
		// Update all vertices
		void UpdateMeshGeometry();
		// Update a subset of all vertices
		void UpdateMeshGeometry(std::vector<Vertex*> vertices);
		// Update a single vertex
		void UpdateMeshGeometry(Vertex* vertex);

		// Display the model by sending the vertices, faces and normals arrays to the graphic card
		void Display();

		void SetRenderMode(RenderMode renderMode);

		

		void SetVertexSelected(int index, bool selected);
		void ClearVertexSelection();
		void SetEdgeSelected(int index, bool selected);
		void ClearEdgeSelection();
	};
}
