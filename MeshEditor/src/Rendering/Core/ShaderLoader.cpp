#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace Core;
using namespace std;

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

string ShaderLoader::ReadShader(char* fileName)
{
	string shaderCode;
	ifstream file(fileName, ios::in);

	if (!file.good())
	{
		cout << "Can't read file " << fileName << endl;
		terminate();
	}

	file.seekg(0, ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, string source, char* shaderName)
{
	int status = 0;

	GLuint shader = glCreateShader(shaderType);
	const char* shaderCode = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCode, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		int infoLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		vector<char> shaderLog(infoLength);
		glGetShaderInfoLog(shader, infoLength, NULL, &shaderLog[0]);
		cout << "ERROR compiling shader " << shaderName << " :" << endl << &shaderLog[0] << endl;
		return 0;
	}

	return shader;
}

GLuint ShaderLoader::CreateProgram(char* vertexShaderFileName, char* fragmentShaderFileName)
{
	string vertexShader = ReadShader(vertexShaderFileName);
	string fragmentShader = ReadShader(fragmentShaderFileName);

	GLuint vertexShaderId = CreateShader(GL_VERTEX_SHADER, vertexShader, "vertex_shader");
	GLuint fragmentShaderId = CreateShader(GL_FRAGMENT_SHADER, fragmentShader, "fragment_shader");

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
		cout << "ERROR LINKING PROGRAM :" << endl << &programLog[0] << endl;
		return 0;
	}

	return program;
}