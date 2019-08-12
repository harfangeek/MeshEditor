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
										translation(0.0f, 0.0f, 0.0f),
										rotation(0.0f, 0.0f, 0.0f),
										scale(1.0f, 1.0f, 1.0f),
										verticesNormalsUpdated(false),
										facesNormalsUpdated(false),
										renderMode(RenderMode::MESH)																																										
{
	
	SetMesh(mesh);
}

MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(NB_VBO, vboIds);
	glDeleteVertexArrays(NB_VAO, vaoIds);
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

void MeshRenderer::Init(GLuint program)
{
	// Create shader buffers and variables
	glGenVertexArrays(NB_VAO, vaoIds);
	glGenBuffers(NB_VBO, vboIds);
	
	modelMatrixLoc = glGetUniformLocation(program, "model_matrix");
	meshColorLoc = glGetUniformLocation(program, "mesh_color");
	materialTypeLoc = glGetUniformLocation(program, "material_type");	

	InitVAOMesh();
	InitVAOVertices();
	InitVAOFacesNormals();
	InitVAOVerticesNormals();
}

void MeshRenderer::InitVAOMesh()
{
	glBindVertexArray(vaoIds[VAO_MESH]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_NORMALS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(2);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_EDGES_SELECTION]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[VBO_FACES]);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOVertices()
{
	glBindVertexArray(vaoIds[VAO_VERTICES]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO::VBO_VERTICES]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES_SELECTION]);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_EDGES_SELECTION]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOFacesNormals()
{
	glBindVertexArray(vaoIds[VAO_FACES_NORMALS]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_FACES_NORMALS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);
}

void MeshRenderer::InitVAOVerticesNormals()
{
	glBindVertexArray(vaoIds[VAO_VERTICES_NORMALS]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES_NORMALS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindVertexArray(0);
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
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Send the new faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[VBO_FACES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Send the new normals
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);

	// Send the vertices selection
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES_SELECTION]);
	glBufferData(GL_ARRAY_BUFFER, verticesSelection.size() * sizeof(GLint), &verticesSelection.front(), GL_STATIC_DRAW);

	// Send the edges selection
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_EDGES_SELECTION]);
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
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES_NORMALS]);
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
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_FACES_NORMALS]);
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
	if (renderMode & RenderMode::FACES_NORMALS && !facesNormalsUpdated)
		UpdateFacesNormals();
	if (renderMode & RenderMode::VERTICES_NORMALS && !verticesNormalsUpdated)
		UpdateVerticesNormals();
}

// Display the model by sending the vertices, faces and normals arrays to the graphic card
void MeshRenderer::Display()
{
	if (mesh)
	{
		glm::mat4 model_matrix = glm::translate(translation) *
			glm::toMat4(glm::quat(glm::radians(rotation))) *
			glm::scale(scale);
		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model_matrix[0][0]);
		
		if (renderMode & RenderMode::MESH)
			Draw(GL_FILL, GL_TRIANGLES, true, VAO_MESH, faces.size(), mesh->color, MaterialType::MATERIAL_LIGHT);
		if (renderMode & RenderMode::WIREFRAME)
			Draw(GL_LINE, GL_TRIANGLES, true, VAO_MESH, faces.size(), glm::vec4(0.0, 1.0, 1.0, 0.0), MaterialType::MATERIAL_NO_LIGHT);
		if (renderMode & RenderMode::VERTICES)
			Draw(GL_POINT, GL_POINTS, false, VAO_VERTICES, mesh->vertices.size(), glm::vec4(0.0, 0.0, 1.0, 0.0), MaterialType::MATERIAL_NO_LIGHT);
		if (renderMode & RenderMode::FACES_NORMALS)
			Draw(GL_LINE, GL_LINES, false, VAO_FACES_NORMALS, mesh->faces.size() * 2, glm::vec4(1.0, 1.0, 0.0, 0.0), MaterialType::MATERIAL_NO_LIGHT);
		if (renderMode & RenderMode::VERTICES_NORMALS)
			Draw(GL_LINE, GL_LINES, false, VAO_VERTICES_NORMALS, mesh->vertices.size() * 2, glm::vec4(1.0, 0.0, 1.0, 0.0), MaterialType::MATERIAL_NO_LIGHT);

		glBindVertexArray(0);
	}
}

void MeshRenderer::Draw(GLuint polygonMode, GLuint drawMode, bool elements, VAO vaoId, size_t size, const glm::vec4& color, const MaterialType materialType)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	glUniform4f(meshColorLoc, color.r, color.g, color.b, color.a);
	glUniform1ui(materialTypeLoc, materialType);
	glBindVertexArray(vaoIds[vaoId]);
	if(elements)
		glDrawElements(drawMode, GLsizei(size), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(drawMode, 0, GLsizei(size));
}

void MeshRenderer::SetVertexSelected(int index, bool selected)
{
	verticesSelection[index] = selected ? 1 : 0;

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_VERTICES_SELECTION]);
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

		glBindBuffer(GL_ARRAY_BUFFER, vboIds[VBO_EDGES_SELECTION]);
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
