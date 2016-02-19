#pragma once

#include "Model\Mesh.h"

namespace Operators
{
	class MeshTransformation
	{
		public:
			// Transform a mesh with faces composed of n vertices into a mesh only composed by triangle faces (i.e. 3 vertices per face)
			// Each face with more than three vertices is divided into several new faces
			// @param mesh : a mesh with faces composed of n vertices
			static void Triangulate(Model::Mesh* mesh);
	};
}