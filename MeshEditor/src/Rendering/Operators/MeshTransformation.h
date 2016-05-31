#pragma once

#include "Rendering\Model\Mesh.h"

namespace Rendering
{
	namespace Operators
	{
		class MeshTransformation
		{
		public:
			// Transform a mesh with faces composed of n vertices into a mesh only composed by triangle faces (i.e. 3 vertices per face)
			// Each face with more than three vertices is divided into several new faces
			// @param mesh : a mesh with faces composed of n vertices
			static void Triangulate(Rendering::Model::Mesh* mesh);

			// Inflate the mesh by moving each vertex along its normal
			static void Inflate(Rendering::Model::Mesh* mesh, float value);
		};
	}
}