#include "Rendering/ShaderLoader.h"
#include "Rendering/Utility.h"
#include <iostream>
#include <vector>

using namespace Rendering;
using namespace std;

GLuint ShaderLoader::CreateShader(GLenum shaderType, char* source)
{
	int status = 0;

	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		int infoLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		vector<char> shaderLog(infoLength);
		glGetShaderInfoLog(shader, infoLength, NULL, &shaderLog[0]);
		cout << "ERROR compiling shader "  << endl << &shaderLog[0] << endl; // To be replaced with exception
		return 0;
	}

	return shader;
}

GLuint ShaderLoader::CreateProgram(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName)
{
	char *vertexShader, *fragmentShader;
	Utility::GetFileContents(vertexShaderFileName, vertexShader);
	Utility::GetFileContents(fragmentShaderFileName, fragmentShader);

	GLuint vertexShaderId = CreateShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragmentShaderId = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);

	int linkRes = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShaderId);
	glAttachShader(program, fragmentShaderId);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkRes);
	if (linkRes == GL_FALSE)
	{
		int infoLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		vector<char> programLog(infoLength);
		glGetProgramInfoLog(program, infoLength, NULL, &programLog[0]);
		cout << "ERROR LINKING PROGRAM :" << endl << &programLog[0] << endl; // To be replaced with exception
		return 0;
	}

	return program;
}