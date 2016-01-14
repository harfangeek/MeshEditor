#include <iostream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"

#include "Model\Mesh.h"
#include "Operators\ObjReader.h"
#include "Operators\MeshConverter.h"
#include "Core\ShaderLoader.h"
#include "Core\MeshRenderer.h"

#include <vector>

void renderScene();
void init();

GLuint program;
Model::Mesh* mesh;
Core::MeshRenderer meshRenderer;

GLuint projection_matrix_loc;
GLuint view_matrix_loc;
GLuint normal_matrix_loc;

int main(int argc, char** argv)
{
	// Freeglut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Title");

	// Glew init
	glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
	{
		std::cout << "GLEW version is 3.3" << std::endl;
	}
	else
	{
		std::cout << "Glew 3.3 not supported" << std::endl;
	}

	init();	

	glutDisplayFunc(renderScene);
	glutMainLoop();
	glDeleteProgram(program);	

	return 0;
}

/*void init()
{
	std::vector<glm::vec3> vertices;
	std::vector<std::vector<unsigned int>> faces;
	Operators::ObjReader::Read("Models\\cube.obj", vertices, faces);
	Operators::MeshConverter::ArrayToHalfEdgeStructure(mesh, vertices, faces);
	meshRenderer.SetMesh(&mesh);

	glEnable(GL_DEPTH_TEST);
	Core::ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("src\\Core\\Shaders\\vertexShader.glsl", "src\\Core\\Shaders\\fragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}*/

/*void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//meshRenderer.Display();

	glutSwapBuffers();
}*/

void init()
{
	std::vector<glm::vec3> vertices;
	std::vector<std::vector<unsigned int>> faces;
	Operators::ObjReader::Read("Models\\apple.obj", vertices, faces);
	mesh = new Model::Mesh();
	Operators::MeshConverter::ArrayToHalfEdgeStructure(*mesh, vertices, faces);

	std::vector<std::string> errors;
	mesh->Check(errors);
	for (unsigned int i = 0; i < errors.size(); i++)
		std::cout << errors[i].c_str() << std::endl;

	meshRenderer.SetMesh(mesh);

	glEnable(GL_DEPTH_TEST);
	Core::ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("src\\Core\\Shaders\\vertexShader.glsl", "src\\Core\\Shaders\\fragmentShader.glsl");
	glUseProgram(program);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glBindFragDataLocation(program, 0, "color_out");

	projection_matrix_loc = glGetUniformLocation(program, "myprojection_matrix");
	view_matrix_loc = glGetUniformLocation(program, "myview_matrix");
	normal_matrix_loc = glGetUniformLocation(program, "mynormal_matrix");
}

void renderScene()
{
	int Glut_w = 600, Glut_h = 600;
	float fovy = 90;
	float zNear = 0.2f;
	float zFar = 6000;

	glm::vec3 camera_eye(0, 0, 2);
	glm::vec3 camera_up(0, 1, 0);
	glm::vec3 camera_forward(0, 0, -1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, Glut_w, Glut_h);

	glm::mat4 projection_matrix =
		glm::perspective(fovy, Glut_w / (float)Glut_h, zNear, zFar);
	glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix =
		glm::lookAt(camera_eye,
		camera_eye + camera_forward,
		camera_up);

	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

	glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(view_matrix)));
	glUniformMatrix3fv(normal_matrix_loc, 1, GL_FALSE, &normal_matrix[0][0]);

	meshRenderer.Display();

	//glFlush();
	glutSwapBuffers();
}