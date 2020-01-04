#pragma once

#include <vector>
#include <map>
#include <array>
#include "GL/gl3w.h"
#include "GLM/glm.hpp"

namespace Rendering
{
	class Mesh;
	class Vertex;
	
	enum class RenderMode : unsigned char {
		None = 0,
		Mesh = 1,
		Wireframe = 1 << 2,
		Vertices = 1 << 3,
		FacesNormals = 1 << 4,
		VerticesNormals = 1 << 5
	};

	inline RenderMode operator|(RenderMode l, RenderMode r) { return static_cast<RenderMode>(static_cast<unsigned char>(l) | static_cast<unsigned char>(r)); }
	inline RenderMode& operator|=(RenderMode& l, RenderMode r) { return l = l | r; }
	inline bool operator&(RenderMode l, RenderMode r) { return static_cast<unsigned char>(l) & static_cast<unsigned char>(r); }

	enum class MaterialType {
		Light = 0,
		NoLight
	};

	class MeshRenderer
	{
	private:

		static constexpr unsigned int NB_VAO = 4;
		static constexpr unsigned int NB_VBO = 7;

		enum class VAO {
			Mesh = 0,
			Vertices,
			FacesNormals,
			VerticesNormals
		};

		enum class VBO {
			Vertices = 0,
			Faces,
			Normals,
			FacesNormals,
			VerticesNormals,
			VerticesSelection,
			EdgesSelection
		};

		Mesh* mesh; // Mesh in half-edge structure

		// Rendering parameters		
		RenderMode renderMode;

		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec4 meshColor, wireframeColor, verticesColor, facesNormalsColor, verticesNormalsColor;

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
		std::map<unsigned int, std::array<GLuint, NB_VAO>> vaoIds;
		std::array<GLuint, NB_VBO> vboIds;

		bool verticesNormalsUpdated;
		bool facesNormalsUpdated;

		// Shaders variables		
		GLuint modelMatrixLoc;
		GLuint meshColorLoc;
		GLuint materialTypeLoc;

		void Clean();

		void InitVAOMesh(unsigned int context);
		void InitVAOVertices(unsigned int context);
		void InitVAOFacesNormals(unsigned int context);
		void InitVAOVerticesNormals(unsigned int context);

		void Draw(GLuint polygonMode, GLuint drawMode, bool elements, VAO vaoId, size_t size, const glm::vec4& color, const MaterialType materialType, unsigned int context=0);

		void UpdateFacesNormals();
		void UpdateVerticesNormals();
		void GenerateFacesNormals();
		void GenerateVerticesNormals();

	public:
		MeshRenderer(Mesh* mesh = NULL);
		~MeshRenderer();

		/* The following function must be called once at least one OpenGL context has been created and made current.
		*
		*  This class supports shared GL context (multiple GL context sharing the same objects).
		*  It is useful when you want to draw the same objects into multiple windows but you're forced 
		*  to have a separate GL context for each window.
		*
		*  If you're not using shared contexts you can skip this and just use Init() and Release() without argument.
		*
		*  The context parameter in an abstract identifier to identify the current OpenGL context.
		*  The user has to maintain a relationship with this identifier and the right GL context.
		*  The user has to call each of these functions with the right GL context made current.
		*/
		void Init(GLuint program, unsigned int context = 0);
		void InitForContext(unsigned int context);
		void Release();
		void ReleaseFromContext(unsigned int context);

		void SetMesh(Mesh* mesh);
		Mesh* GetMesh();

		// Display the model by sending the vertices, faces and normals arrays to the graphic card
		// Initialize the renderer for the given context if not already done
		void Display(unsigned int context = 0);

		void SetTranslation(glm::vec3 translation);
		glm::vec3 GetTranslation();
		void SetRotation(glm::vec3 rotation);
		glm::vec3 GetRotation();
		void SetScale(glm::vec3 scale);
		glm::vec3 GetScale();

		void SetMeshColor(glm::vec4 color);
		glm::vec4 GetMeshColor();
		void SetWireframeColor(glm::vec4 color);
		glm::vec4 GetWireframeColor();
		void SetVerticesColor(glm::vec4 color);
		glm::vec4 GetVerticesColor();
		void SetFacesNormalsColor(glm::vec4 color);
		glm::vec4 GetFacesNormalsColor();
		void SetVerticesNormalsColor(glm::vec4 color);
		glm::vec4 GetVerticesNormalsColor();

		// Must be called whenever the mesh connectivity has changed (new or removed vertices/edge/face)
		// Update vertices, faces and normals arrays
		void UpdateMeshConnectivity();

		// UpdateMeshGeomtry() methods must be called whenever the mesh geometry has changed (i.e. some vertices' positions have changed)
		// Update all vertices
		void UpdateMeshGeometry();
		// Update a subset of all vertices
		void UpdateMeshGeometry(std::vector<Vertex*> vertices);
		// Update a single vertex
		void UpdateMeshGeometry(Vertex* vertex);

		void SetRenderMode(RenderMode renderMode);

		

		void SetVertexSelected(int index, bool selected);
		void ClearVertexSelection();
		void SetEdgeSelected(int index, bool selected);
		void ClearEdgeSelection();
	};
}
