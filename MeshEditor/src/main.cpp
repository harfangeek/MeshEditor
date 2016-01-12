#include <iostream>

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"

#include "Model\Mesh.h"
#include "Operators\ObjReader.h"
#include "Operators\MeshConverter.h"
#include "Core\ShaderLoader.h"

#include <vector>

void renderScene();
void init();

GLuint program;

int main(int argc, char** argv)
{
	// Freeglut init
	/*glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
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
	glDeleteProgram(program);*/

	std::vector<glm::vec3> vertices;
	std::vector<std::vector<unsigned int>> faces;
	Operators::ObjReader::Read("apple.obj", vertices, faces);
	Model::Mesh mesh;
	Operators::MeshConverter::ArrayToHalfEdgeStructure(mesh, vertices, faces);

	std::vector<std::string> errors;
	mesh.Check(errors);
	for (unsigned int i = 0; i < errors.size(); i++)
		std::cout << errors[i].c_str() << std::endl;


	return 0;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	ShaderLoader shaderLoader;
	program = shaderLoader.CreateProgram("src\\Core\\Shaders\\vertexShader.glsl", "src\\Core\\Shaders\\fragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}