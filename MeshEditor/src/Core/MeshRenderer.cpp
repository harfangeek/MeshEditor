#include "Core\MeshRenderer.h"
#include "Operators\MeshConverter.h"
#include "Core\ShaderLoader.h"
#include "Model\Vertex.h"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtx\rotate_vector.hpp"

using namespace Core;
using namespace Model;
using namespace std;

MeshRenderer::MeshRenderer(int viewportWidth, int viewportHeight, Model::Mesh* mesh) :	cameraEye(0, 0, 2),
																						cameraUp(0, 1, 0), 
																						cameraForward(0, 0, -1),
																						fovy(90.0f),
																						zNear(0.02f),
																						zFar(5000.0f),
																						renderMode(RenderMode::MESH),
																						facesNormalsUpdated(false),
																						verticesNormalsUpdated(false)
{
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	SetMesh(mesh);
}

MeshRenderer::~MeshRenderer()
{
	glDeleteProgram(program);
}

void MeshRenderer::SetMesh(Model::Mesh* mesh)
{
	if (mesh != NULL)
	{
		this->mesh = mesh;
		UpdateMesh();
	}
}

Model::Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Init()
{
	// OpenGL init
	glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
		std::cout << "GLEW version is 3.3" << std::endl;
	else
		std::cout << "Glew 3.3 not supported" << std::endl;
	
	// Create shaders
	Core::ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\vertexShader.glsl", "Shaders\\fragmentShader.glsl");	
		
	// Create shader buffers and variables
	glGenBuffers(NB_BUFFER, buffers);
	projection_matrix_loc = glGetUniformLocation(program, "myprojection_matrix");
	view_matrix_loc = glGetUniformLocation(program, "myview_matrix");
	color_loc = glGetUniformLocation(program, "vertex_color");
}

// Must be called whenever the mesh structure has changed.
// Update vertices, faces and normals arrays
void MeshRenderer::UpdateMesh()
{
	// Update vertices/faces/normals arrays from half-edge structure
	Operators::MeshConverter::HalfEdgeStructureToArray(mesh, vertices, faces, normals);
	facesNormalsUpdated = false;
	verticesNormalsUpdated = false;
	
	// Send the new vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Send the new faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUF_FACES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Send the new normals
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUF_NORMALS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);
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
	Vertex* vertex;
	verticesNormals.clear();
	for (unsigned int i = 0; i < mesh->vertices.size(); i++)
	{
		vertex = mesh->vertices[i];
		glm::vec3 v1 = vertex->position;
		glm::vec3 v2 = vertex->position + 0.03f * vertex->normal;
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
	Face* face;
	vector<Vertex*> vertices;
	facesNormals.clear();
	for (unsigned int i = 0; i < mesh->faces.size(); i++)
	{
		face = mesh->faces[i];
		face->ListVertices(vertices);

		glm::vec3 v1(0.0f, 0.0f, 0.0f);
		for (unsigned int j = 0; j < vertices.size(); j++)
		{
			v1 += vertices[j]->position;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, viewportWidth, viewportHeight);

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
	if (renderMode & RenderMode::SILOUHETTE)
		DisplaySilouhette();
}

void MeshRenderer::DrawMesh(unsigned int drawMode, GLuint program, glm::vec4 color)
{
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);
	glUseProgram(program);

	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

	glUniform4f(color_loc, color.r, color.g, color.b, color.a);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_VERTICES]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BUF_NORMALS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BUF_FACES]);
	glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
}

void MeshRenderer::DrawNormals(BufferId buffer, GLuint program, glm::vec4 color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(program);

	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

	glUniform4f(color_loc, color.r, color.g, color.b, color.a);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[buffer]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_LINES, 0, vertices.size());
}

void MeshRenderer::DisplayMesh()
{			
	DrawMesh(GL_FILL, program, glm::vec4(1.0, 0.0, 0.0, 0.0));
}

void MeshRenderer::DisplayWireframe()
{
	DrawMesh(GL_LINE, program, glm::vec4(0.0, 1.0, 0.0, 0.0));
}

void MeshRenderer::DisplayVertices()
{
	glPointSize(5.0f);
	DrawMesh(GL_POINT, program, glm::vec4(0.0, 0.0, 1.0, 0.0));
}

void MeshRenderer::DisplayFacesNormals()
{
	DrawNormals(BufferId::BUF_FACES_NORMALS, program, glm::vec4(1.0, 1.0, 0.0, 0.0));
}

void MeshRenderer::DisplayVerticesNormals()
{
	DrawNormals(BufferId::BUF_VERTICES_NORMALS, program, glm::vec4(1.0, 0.0, 1.0, 0.0));
}

void MeshRenderer::DisplaySilouhette()
{

}

void MeshRenderer::Rotate(float x, float y)
{
	float theta = 4.0f * (fabs(x) + fabs(y));

	glm::vec3 cameraRight = glm::cross(cameraUp, -cameraForward);
	// Compute a vector between (1, 0, 0) (only X rotation) and (0, 1, 0) (only Y rotation)
	// This vector represents the rotation axis combining the two rotations
	glm::vec3 rotationAxis = x * -cameraUp + y * -cameraRight; 
	rotationAxis = glm::normalize(rotationAxis);

	cameraForward = glm::rotate(cameraForward, theta, rotationAxis);
	cameraUp = glm::rotate(cameraUp, theta, rotationAxis);
	cameraEye = glm::rotate(cameraEye, theta, rotationAxis);

	cameraUp = glm::normalize(cameraUp);
	cameraEye = glm::normalize(cameraEye);
	cameraForward = glm::normalize(cameraForward);
}
