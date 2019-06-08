#pragma once

#include "GL/gl3w.h"
#include <string>

namespace Rendering
{
	class ShaderLoader
	{
	public:
		static GLuint CreateProgram(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);

	private:
		static GLuint CreateShader(GLenum shaderType, char* source);
	};
}
