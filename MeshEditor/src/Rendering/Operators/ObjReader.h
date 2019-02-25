#pragma once

#include "Rendering/Model/Mesh.h"

#define GLM_FORCE_SILENT_WARNINGS 1
#include "GLM/glm.hpp"
#include "GL/gl3w.h"

#include <vector>
#include <string>

namespace Rendering
{
	namespace Operators
	{
		class ObjReader
		{
		public:
			static bool ReadObj(const std::string &path, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces);
			static bool WriteObj(const std::string &path, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& faces);
			static Rendering::Model::Mesh* LoadMesh(const std::string &path);
			static void SaveMesh(const Rendering::Model::Mesh& mesh, const std::string& path);
		};
	}
}
