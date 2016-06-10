#pragma once

#include <iostream>

#include "Dependencies\glew\include\glew.h"
#include "Dependencies\freeglut\include\freeglut.h"

namespace Rendering
{
	namespace Core
	{
		class ShaderLoader
		{
		public:
			ShaderLoader();
			~ShaderLoader();
			GLuint CreateProgram(char* vertexShaderFileName, char* fragmentShaderFileName);

		private:
			std::string ReadShader(char* fileName);
			GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);
		};
	}
}
