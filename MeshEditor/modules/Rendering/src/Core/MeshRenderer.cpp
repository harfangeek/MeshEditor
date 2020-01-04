#include "Rendering/MeshRenderer.h"
#include "Rendering/MeshConverter.h"
#include "Rendering/ShaderLoader.h"
#include "Rendering/Vertex.h"
#include "Rendering/Face.h"
#include "Rendering/HalfEdge.h"
#include "Rendering/Mesh.h"

#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/quaternion.hpp"

using namespace Rendering;
using namespace std;

MeshRenderer::MeshRenderer(Mesh* mesh) : mesh(mesh),
										renderMode(RenderMode::Mesh),
										translation(0.0f, 0.0f, 0.0f),
										rotation(0.0f, 0.0f, 0.0f),
										scale(1.0f, 1.0f, 1.0f),
										meshColor(0.0f, 1.0f, 0.0f, 1.0f),
										wireframeColor(0.0, 1.0, 1.0, 0.0),
										verticesColor(0.0, 0.0, 1.0, 0.0),
										facesNormalsColor(1.0, 1.0, 0.0, 0.0),
										verticesNormalsColor(1.0, 0.0, 1.0, 0.0),
										verticesNormalsUpdated(false),
										facesNormalsUpdated(false)
{
	
	SetMesh(mesh);
}

MeshRenderer::~MeshRenderer()
{
	Release();
}

void MeshRenderer::Clean()
{
	vertices.clear();
	faces.clear();
	normals.clear();
	verticesNormals.clear();
	facesNormals.clear();
	verticesSelection.clear();
	edgesSelection.clear();
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	if (mesh != NULL)
	{
		Clean();
		this->mesh = mesh;
		UpdateMeshConnectivity();
	}
}

Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Init(GLuint program, unsigned int context)
{
	// Create shader buffers and variables
	if (vaoIds.size() == 0)
	{
		glGenBuffers(NB_VBO, vboIds.data());
		InitForContext(context);

		modelMatrixLoc = glGetUniformLocation(program, "model_matrix");
		meshColorLoc = glGetUniformLocation(program, "mesh_color");
		materialTypeLoc = glGetUniformLocation(program, "material_type");
	}
}

void MeshRenderer::InitForContext(unsigned int context)
{
	if (vaoIds.count(context) == 0)
	{
		glGenVertexArrays(NB_VAO, vaoIds[context].data());

		InitVAOMesh(context);
		InitVAOVertices(context);
		InitVAOFacesNormals(context);
		InitVAOVerticesNormals(context);
	}
}

void MeshRenderer::InitVAOMesh(unsigned int context)
{
	glBindVertexArray(vaoIds[context][static_cast<GLuint>(VAO::Mesh)]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Vertices)]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Normals)]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(2);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::EdgesSelection)]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Faces)]);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOVertices(unsigned int context)
{
	glBindVertexArray(vaoIds[context][static_cast<GLuint>(VAO::Vertices)]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Vertices)]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::VerticesSelection)]);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::EdgesSelection)]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOFacesNormals(unsigned int context)
{
	glBindVertexArray(vaoIds[context][static_cast<GLuint>(VAO::FacesNormals)]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::FacesNormals)]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOVerticesNormals(unsigned int context)
{
	glBindVertexArray(vaoIds[context][static_cast<GLuint>(VAO::VerticesNormals)]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::VerticesNormals)]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);
}

void MeshRenderer::ReleaseFromContext(unsigned int context)
{
	auto ids = vaoIds.find(context);
	if (ids != vaoIds.end())
	{
		glDeleteVertexArrays(NB_VAO, ids->second.data());
		vaoIds.erase(context);
	}
}

void MeshRenderer::Release()
{
	glDeleteBuffers(NB_VBO, vboIds.data());

	// If only one context, assume we are in the right GL Context to release its VAO (no shared contexts)
	if (vaoIds.size() == 1)
		ReleaseFromContext(vaoIds.begin()->first);

	Clean();
}

// Must be called whenever the mesh connectivity has changed (new or removed vertices/edges/faces)
// Update vertices, faces and normals arrays
void MeshRenderer::UpdateMeshConnectivity()
{
	// Update vertices/faces/normals arrays from half-edge structure
	vertices.clear();
	faces.clear();
	normals.clear();
	MeshConverter::HalfEdgeStructureToArray(*mesh, vertices, faces, normals);
	
	verticesSelection.clear();
	verticesSelection.resize(vertices.size());
	std::fill(verticesSelection.begin(), verticesSelection.end(), 0);
	
	edgesSelection.clear();
	edgesSelection.resize(vertices.size());
	std::fill(edgesSelection.begin(), edgesSelection.end(), 0);
		
	facesNormalsUpdated = false;
	verticesNormalsUpdated = false;

	// Send the new vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Vertices)]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Send the new faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Faces)]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Send the new normals
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::Normals)]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);

	// Send the vertices selection
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::VerticesNormals)]);
	glBufferData(GL_ARRAY_BUFFER, verticesSelection.size() * sizeof(GLint), &verticesSelection.front(), GL_STATIC_DRAW);

	// Send the edges selection
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::EdgesSelection)]);
	glBufferData(GL_ARRAY_BUFFER, edgesSelection.size() * sizeof(GLint), &edgesSelection.front(), GL_STATIC_DRAW);

	UpdateFacesNormals();
	UpdateVerticesNormals();
}

void MeshRenderer::UpdateVerticesNormals()
{
	if (!verticesNormalsUpdated && this->mesh)
	{
		GenerateVerticesNormals();

		// Send the new normals segments vertices
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::VerticesNormals)]);
		glBufferData(GL_ARRAY_BUFFER, verticesNormals.size() * sizeof(GLfloat), &verticesNormals.front(), GL_STATIC_DRAW);

		verticesNormalsUpdated = true;
	}
}

void MeshRenderer::GenerateVerticesNormals()
{
	glm::vec3 v1, v2;
	verticesNormals.clear();
	vertices.reserve(mesh->vertices.size() * 6);
	for(auto vertex : mesh->vertices)
	{
		v1 = vertex->position;
		v2 = vertex->position + 0.03f * vertex->normal;
		verticesNormals.push_back(v1.x);
		verticesNormals.push_back(v1.y);
		verticesNormals.push_back(v1.z);
		verticesNormals.push_back(v2.x);
		verticesNormals.push_back(v2.y);
		verticesNormals.push_back(v2.z);
	}
}

void MeshRenderer::UpdateFacesNormals()
{
	if (!facesNormalsUpdated && this->mesh)
	{
		GenerateFacesNormals();

		// Send the new normals segments faces
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::FacesNormals)]);
		glBufferData(GL_ARRAY_BUFFER, facesNormals.size() * sizeof(GLfloat), &facesNormals.front(), GL_STATIC_DRAW);

		facesNormalsUpdated = true;
	}
}

void MeshRenderer::GenerateFacesNormals()
{
	facesNormals.clear();
	facesNormals.reserve(mesh->faces.size() * 6);
	for(auto face : mesh->faces)
	{		
		vector<Vertex*> vertices = face->ListVertices();

		glm::vec3 v1(0.0f, 0.0f, 0.0f);
		for(auto vertex : vertices)
		{
			v1 += vertex->position;
		}
		v1 /= vertices.size();
		glm::vec3 v2 = v1 + 0.03f * face->normal;

		facesNormals.push_back(v1.x);
		facesNormals.push_back(v1.y);
		facesNormals.push_back(v1.z);
		facesNormals.push_back(v2.x);
		facesNormals.push_back(v2.y);
		facesNormals.push_back(v2.z);
	}
}

void MeshRenderer::SetRenderMode(RenderMode renderMode)
{
	this->renderMode = renderMode;
	if (renderMode & RenderMode::FacesNormals && !facesNormalsUpdated)
		UpdateFacesNormals();
	if (renderMode & RenderMode::VerticesNormals && !verticesNormalsUpdated)
		UpdateVerticesNormals();
}

// Display the model by sending the vertices, faces and normals arrays to the graphic card
void MeshRenderer::Display(unsigned int context)
{
	if (mesh)
	{
		if (vaoIds.count(context) == 0)
			InitForContext(context);

		glm::mat4 model_matrix = glm::translate(translation) *
			glm::toMat4(glm::quat(glm::radians(rotation))) *
			glm::scale(scale);
		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model_matrix[0][0]);

		if (renderMode & RenderMode::Mesh)
			Draw(GL_FILL, GL_TRIANGLES, true, VAO::Mesh, faces.size(), meshColor, MaterialType::Light, context);
		if (renderMode & RenderMode::Wireframe)
			Draw(GL_LINE, GL_TRIANGLES, true, VAO::Mesh, faces.size(), wireframeColor, MaterialType::NoLight, context);
		if (renderMode & RenderMode::Vertices)
			Draw(GL_POINT, GL_POINTS, false, VAO::Vertices, mesh->vertices.size(), verticesColor, MaterialType::NoLight, context);
		if (renderMode & RenderMode::FacesNormals)
			Draw(GL_LINE, GL_LINES, false, VAO::FacesNormals, mesh->faces.size() * 2, facesNormalsColor, MaterialType::NoLight, context);
		if (renderMode & RenderMode::VerticesNormals)
			Draw(GL_LINE, GL_LINES, false, VAO::VerticesNormals, mesh->vertices.size() * 2, verticesNormalsColor, MaterialType::NoLight, context);

		glBindVertexArray(0);
	}
}

void MeshRenderer::Draw(GLuint polygonMode, GLuint drawMode, bool elements, VAO vaoId, size_t size, const glm::vec4& color, const MaterialType materialType, unsigned int context)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	glUniform4f(meshColorLoc, color.r, color.g, color.b, color.a);
	glUniform1ui(materialTypeLoc, static_cast<GLuint>(materialType));
	glBindVertexArray(vaoIds[context][static_cast<GLuint>(vaoId)]);
	if(elements)
		glDrawElements(drawMode, GLsizei(size), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(drawMode, 0, GLsizei(size));
}

void MeshRenderer::SetVertexSelected(int index, bool selected)
{
	verticesSelection[index] = selected ? 1 : 0;

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::VerticesSelection)]);
	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(GLint), sizeof(GLint), &verticesSelection[index]);
}

void MeshRenderer::ClearVertexSelection()
{
	for (unsigned int i = 0; i < verticesSelection.size(); i++)
		SetVertexSelected(i, false);
}

void MeshRenderer::SetEdgeSelected(int index, bool selected)
{
	if (mesh) {
		int vertex1 = mesh->halfEdges[index]->source->index;
		int vertex2 = mesh->halfEdges[index]->next->source->index;

		edgesSelection[vertex1] = selected ? 1 : 0;
		edgesSelection[vertex2] = selected ? 1 : 0;

		glBindBuffer(GL_ARRAY_BUFFER, vboIds[static_cast<GLuint>(VBO::EdgesSelection)]);
		glBufferSubData(GL_ARRAY_BUFFER, vertex1 * sizeof(GLint), sizeof(GLint), &edgesSelection[vertex1]);
		glBufferSubData(GL_ARRAY_BUFFER, vertex2 * sizeof(GLint), sizeof(GLint), &edgesSelection[vertex2]);
	}
}

void MeshRenderer::ClearEdgeSelection()
{
	for (unsigned int i = 0; i < edgesSelection.size(); i++)
		SetEdgeSelected(i, false);
}

void MeshRenderer::SetTranslation(glm::vec3 translation)
{
	this->translation = translation;
}

glm::vec3 MeshRenderer::GetTranslation()
{
	return translation;
}

void MeshRenderer::SetRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

glm::vec3 MeshRenderer::GetRotation()
{
	return rotation;
}
void MeshRenderer::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 MeshRenderer::GetScale()
{
	return scale;
}

void MeshRenderer::SetMeshColor(glm::vec4 color)
{
	meshColor = color;
}

glm::vec4 MeshRenderer::GetMeshColor()
{
	return meshColor;
}

void MeshRenderer::SetWireframeColor(glm::vec4 color)
{
	wireframeColor = color;
}

glm::vec4 MeshRenderer::GetWireframeColor()
{
	return wireframeColor;
}

void MeshRenderer::SetVerticesColor(glm::vec4 color)
{
	verticesColor = color;
}

glm::vec4 MeshRenderer::GetVerticesColor()
{
	return verticesColor;
}

void MeshRenderer::SetFacesNormalsColor(glm::vec4 color)
{
	facesNormalsColor = color;
}

glm::vec4 MeshRenderer::GetFacesNormalsColor()
{
	return facesNormalsColor;
}

void MeshRenderer::SetVerticesNormalsColor(glm::vec4 color)
{
	verticesNormalsColor = color;
}

glm::vec4 MeshRenderer::GetVerticesNormalsColor()
{
	return verticesNormalsColor;
}
