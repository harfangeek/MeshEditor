#include "Rendering/Core/MeshRenderer.h"
#include "Rendering/Operators/MeshConverter.h"
#include "Rendering/Operators/ShaderLoader.h"
#include "Rendering/Model/Vertex.h"
#include "Rendering/Model/Face.h"
#include "Rendering/Model/HalfEdge.h"
#include "Rendering/Model/Mesh.h"

#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/quaternion.hpp"

using namespace Rendering;
using namespace Rendering::Core;
using namespace Rendering::Model;
using namespace std;

MeshRenderer::MeshRenderer(int viewportWidth, int viewportHeight, Model::Mesh* mesh) : mesh(mesh),
																						translation(0.0f, 0.0f, 0.0f),
																						rotation(0.0f, 0.0f, 0.0f),
																						scale(1.0f, 1.0f, 1.0f),
																						verticesNormalsUpdated(false),
																						facesNormalsUpdated(false),
																						cameraEye(0, 0, 2),
																						cameraUp(0, 1, 0), 
																						cameraForward(0, 0, -1),
																						fovy(45.0f),
																						zNear(0.01f),
																						zFar(5000.0f),
																						renderMode(RenderMode::MESH),
																						lightType(LightType::AMBIANT),	
																						lightColor(1.0f, 1.0f, 1.0f, 1.0f),
																						lightPosition(0.0f, 0.0f, 4.0f),
																						lightDirection(0.0f, -1.0f, 0.0f),
																						lightAngle(30.0f)																					
{
	SetViewPort(viewportWidth, viewportHeight);
	SetMesh(mesh);
}

MeshRenderer::~MeshRenderer()
{
	glDeleteBuffers(NB_BUFFER, buffers);
	glDeleteProgram(program);
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

void MeshRenderer::SetMesh(Model::Mesh* mesh)
{
	if (mesh != NULL)
	{
		Clean();
		this->mesh = mesh;
		UpdateMeshConnectivity();
	}
}

void MeshRenderer::SetViewPort(int viewportWidth, int viewportHeight)
{
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
}

Model::Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Init()
{
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	
	// Create shaders
	program = Operators::ShaderLoader::CreateProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
		
	// Create shader buffers and variables
	glGenVertexArrays(1, &vao);
	glGenBuffers(NB_BUFFER, buffers);
	projectionMatrixLoc = glGetUniformLocation(program, "projection_matrix");
	viewMatrixLoc = glGetUniformLocation(program, "view_matrix");
	modelMatrixLoc = glGetUniformLocation(program, "model_matrix");
	meshColorLoc = glGetUniformLocation(program, "mesh_color");
	lightTypeLoc = glGetUniformLocation(program, "light_type");
	lightColorLoc = glGetUniformLocation(program, "light_color");
	lightPositionLoc = glGetUniformLocation(program, "light_position");
	lightDirectionLoc = glGetUniformLocation(program, "light_direction");
	lightAngleLoc = glGetUniformLocation(program, "light_angle");
}

// Must be called whenever the mesh connectivity has changed (new or removed vertices/edges/faces)
// Update vertices, faces and normals arrays
void MeshRenderer::UpdateMeshConnectivity()
{
	// Update vertices/faces/normals arrays from half-edge structure
	vertices.clear();
	faces.clear();
	normals.clear();
	Operators::MeshConverter::HalfEdgeStructureToArray(*mesh, vertices, faces, normals);
	
	verticesSelection.clear();
	verticesSelection.resize(vertices.size());
	std::fill(verticesSelection.begin(), verticesSelection.end(), 0);
	
	edgesSelection.clear();
	edgesSelection.resize(vertices.size());
	std::fill(edgesSelection.begin(), edgesSelection.end(), 0);
		
	facesNormalsUpdated = false;
	verticesNormalsUpdated = false;

	// Send the new vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Send the new faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUF_FACES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Send the new normals
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);

	// Send the vertices selection
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES_SELECTION]);
	glBufferData(GL_ARRAY_BUFFER, verticesSelection.size() * sizeof(GLint), &verticesSelection.front(), GL_STATIC_DRAW);

	// Send the edges selection
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_EDGES_SELECTION]);
	glBufferData(GL_ARRAY_BUFFER, edgesSelection.size() * sizeof(GLint), &edgesSelection.front(), GL_STATIC_DRAW);
}

void MeshRenderer::UpdateVerticesNormals()
{
	GenerateVerticesNormals();

	// Send the new normals segments vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, verticesNormals.size() * sizeof(GLfloat), &verticesNormals.front(), GL_STATIC_DRAW);

	verticesNormalsUpdated = true;
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
	GenerateFacesNormals();

	// Send the new normals segments faces
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_FACES_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, facesNormals.size() * sizeof(GLfloat), &facesNormals.front(), GL_STATIC_DRAW);

	facesNormalsUpdated = true;
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

void MeshRenderer::SetLightType(LightType lightType)
{
	this->lightType = lightType;
}

void MeshRenderer::SetLightColor(glm::vec4 color)
{
	lightColor = color;
}

void MeshRenderer::SetLightPosition(glm::vec3 position)
{
	lightPosition = position;
}

void MeshRenderer::SetLightDirection(glm::vec3 direction)
{
	lightDirection = direction;
}

void MeshRenderer::SetLightAngle(float angle)
{
	lightAngle = angle;
}

// Display the model by sending the vertices, faces and normals arrays to the graphic card
void MeshRenderer::Display()
{
	if (mesh)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, viewportWidth, viewportHeight);

		glBindVertexArray(vao);

		if (renderMode & RenderMode::MESH)
			DisplayMesh();
		if (renderMode & RenderMode::WIREFRAME)
			DisplayWireframe();
		if (renderMode & RenderMode::VERTICES)
			DisplayVertices();
		if (renderMode & RenderMode::FACES_NORMALS)
			DisplayFacesNormals();
		if (renderMode & RenderMode::VERTICES_NORMALS)
			DisplayVerticesNormals();
	}
}

void MeshRenderer::DrawMesh(unsigned int drawMode, GLuint program, glm::vec4 color, LightType lightType)
{
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);
	glUseProgram(program);

	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &view_matrix[0][0]);
	
	glm::mat4 model_matrix = glm::translate(translation) *
		glm::toMat4(glm::quat(glm::radians(rotation))) *
		glm::scale(scale);

	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &model_matrix[0][0]);

	glUniform4f(meshColorLoc, color.r, color.g, color.b, color.a);
	glUniform1ui(lightTypeLoc, lightType);
	glUniform4f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b, lightColor.a);
	glUniform3f(lightPositionLoc, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(lightDirectionLoc, lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform1f(lightAngleLoc, lightAngle);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_NORMALS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(2);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_EDGES_SELECTION]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUF_FACES]);
	glDrawElements(GL_TRIANGLES, GLsizei(faces.size()), GL_UNSIGNED_INT, 0);
}

void MeshRenderer::DrawVertices(BufferId buffer, GLuint program, glm::vec4 color, LightType lightType)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glUseProgram(program);

	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &view_matrix[0][0]);

	glUniform4f(meshColorLoc, color.r, color.g, color.b, color.a);
	glUniform1i(lightTypeLoc, lightType);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES_SELECTION]);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_EDGES_SELECTION]);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 0, 0);

	glDrawArrays(GL_POINTS, 0, GLsizei(mesh->vertices.size()));
}

void MeshRenderer::DrawNormals(BufferId buffer, unsigned int size, GLuint program, glm::vec4 color, LightType lightType)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(program);
	
	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &view_matrix[0][0]);

	glUniform4f(meshColorLoc, color.r, color.g, color.b, color.a);
	glUniform1i(lightTypeLoc, lightType);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glDrawArrays(GL_LINES, 0, size);
}

void MeshRenderer::DisplayMesh()
{			
	DrawMesh(GL_FILL, program, mesh->color, lightType);
}

void MeshRenderer::DisplayWireframe()
{
	DrawMesh(GL_LINE, program, glm::vec4(0.0, 1.0, 0.0, 0.0), LightType::AMBIANT);
}

void MeshRenderer::DisplayVertices()
{
	//glPointSize(5.0f);
	//DrawMesh(GL_POINT, program, glm::vec4(0.0, 0.0, 1.0, 0.0), LightType::AMBIANT);
	DrawVertices(BufferId::BUF_VERTICES, program, glm::vec4(0.0, 0.0, 1.0, 0.0), LightType::AMBIANT);
}

void MeshRenderer::DisplayFacesNormals()
{
	DrawNormals(BufferId::BUF_FACES_NORMALS, GLsizei(mesh->faces.size() * 2), program, glm::vec4(1.0, 1.0, 0.0, 0.0), LightType::AMBIANT);
}

void MeshRenderer::DisplayVerticesNormals()
{
	DrawNormals(BufferId::BUF_VERTICES_NORMALS, GLsizei(mesh->vertices.size() * 2), program, glm::vec4(1.0, 0.0, 1.0, 0.0), LightType::AMBIANT);
}

void MeshRenderer::Rotate(float x, float y)
{
	float theta = 4.0f * (fabs(x) + fabs(y));
	if (theta > 0.00000001)
	{
		glm::vec3 cameraRight = glm::cross(cameraUp, -cameraForward);
		// Compute a vector between (1, 0, 0) (only X rotation) and (0, 1, 0) (only Y rotation)
		// This vector represents the rotation axis combining the two rotations
		glm::vec3 rotationAxis = x * -cameraUp + y * -cameraRight;
		rotationAxis = glm::normalize(rotationAxis);

		cameraForward = glm::rotate(cameraForward, theta, rotationAxis);
		cameraUp = glm::rotate(cameraUp, theta, rotationAxis);
		cameraEye = glm::rotate(cameraEye, theta, rotationAxis);

		cameraUp = glm::normalize(cameraUp);
		//cameraEye = glm::normalize(cameraEye);
		cameraForward = glm::normalize(cameraForward);
	}
}

void MeshRenderer::Translate(float x, float y)
{
	glm::vec3 cameraRight = glm::cross(cameraUp, -cameraForward);
	cameraEye += x * cameraRight;
	cameraEye += y * cameraUp;
}

void MeshRenderer::Zoom(float value)
{
	cameraEye += value * cameraForward;
}

void MeshRenderer::SetVertexSelected(int index, bool selected)
{
	verticesSelection[index] = selected ? 1 : 0;

	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES_SELECTION]);
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

		glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_EDGES_SELECTION]);
		glBufferSubData(GL_ARRAY_BUFFER, vertex1 * sizeof(GLint), sizeof(GLint), &edgesSelection[vertex1]);
		glBufferSubData(GL_ARRAY_BUFFER, vertex2 * sizeof(GLint), sizeof(GLint), &edgesSelection[vertex2]);
	}
}

void MeshRenderer::ClearEdgeSelection()
{
	for (unsigned int i = 0; i < edgesSelection.size(); i++)
		SetEdgeSelected(i, false);
}

int MeshRenderer::GetViewportWidth()
{
	return viewportWidth;
}

int MeshRenderer::GetViewportHeight()
{
	return viewportHeight;
}

float MeshRenderer::GetFovy()
{
	return fovy;
}

float MeshRenderer::GetZNear()
{
	return zNear;
}

float MeshRenderer::GetZFar()
{
	return zFar;
}

glm::vec3 MeshRenderer::GetCameraEye()
{
	return cameraEye;
}

glm::vec3 MeshRenderer::GetCameraUp()
{
	return cameraUp;
}

glm::vec3 MeshRenderer::GetCameraForward()
{
	return cameraForward;
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


