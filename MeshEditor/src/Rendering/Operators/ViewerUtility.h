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
			// Find vertices wich window position (once rendered) is around (x, y), depending of the given precision
			// Selected vertices are find using ray tracing.
			// @param renderer : current mesh renderer (contains the 3D model and rendering information)
			// @param windows : current window
			// @param x : position in x axis
			// @param y : position in y axis
			// @param selectedVertices : vector filled with indices of all found vertices
			static void GetSelectedVertices(Rendering::Core::MeshRenderer* renderer, GUI::Interfaces::Window* window, int x, int y, std::vector<unsigned int> &selectedVertices, float precision=0.0004f);
		};
	}
}