#include "Core\MeshRenderer.h"
#include "Operators\MeshConverter.h"
#include "Core\ShaderLoader.h"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtx\rotate_vector.hpp"

using namespace Core;

MeshRenderer::MeshRenderer(int viewportWidth, int viewportHeight, Model::Mesh* mesh) :	cameraEye(0, 0, 2),
																						cameraUp(0, 1, 0), 
																						cameraForward(0, 0, -1),
																						fovy(90.0f),
																						zNear(0.2f),
																						zFar(5000.0f)
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
		Update();
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

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Create shaders
	Core::ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\vertexShader.glsl", "Shaders\\fragmentShader.glsl");	

	// Set shaders and create shaders variables
	glUseProgram(program);
	projection_matrix_loc = glGetUniformLocation(program, "myprojection_matrix");
	view_matrix_loc = glGetUniformLocation(program, "myview_matrix");

	glGenBuffers(3, buffers);
}

// Must be called whenever the mesh structure has changed.
// Update vertices, faces and normals arrays
void MeshRenderer::Update()
{
	// Update vertices/faces/normals arrays from half-edge structure
	Operators::MeshConverter::HalfEdgeStructureToArray(mesh, vertices, faces, normals);

	// Send the new vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Send the new faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Send the new normals
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, normals.size() * sizeof(float), &normals.front(), GL_STATIC_DRAW);
}

// Display the model by sending the vertices, faces and normals arrays to the graphic card
void MeshRenderer::Display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, viewportWidth, viewportHeight);	

	if (mesh)
	{
		glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
		glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, &projection_matrix[0][0]);

		glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);
		glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
		glDrawElements(GL_TRIANGLE_FAN, faces.size(), GL_UNSIGNED_INT, 0);
	}
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