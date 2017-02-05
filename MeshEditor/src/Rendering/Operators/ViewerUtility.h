#pragma once

#include "Rendering\Core\MeshRenderer.h"
#include "GUI\Interfaces\Window.h"
#include <vector>

namespace Rendering
{
	namespace Operators
	{
		class ViewerUtility
		{
		public:
			// Transform a mesh with faces composed of n vertices into a mesh only composed by triangle faces (i.e. 3 vertices per face)
			// Each face with more than three vertices is divided into several new faces
			// @param mesh : a mesh with faces composed of n vertices
			static void GetSelectedVertices(Rendering::Core::MeshRenderer* renderer, GUI::Interfaces::Window* window, int x, int y, std::vector<unsigned int> &selectedVertices, float precision=0.01);
		};
	}
}