#pragma once

#include <vector>

namespace GUI
{
	class Window;
}

namespace Rendering
{
	class SceneRenderer;
	class Camera;

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
		static void GetSelectedVertices(SceneRenderer* sceneRenderer, Camera* camera, GUI::Window* window, int x, int y, std::vector<unsigned int> &selectedVertices, float precision=0.0004f);
	};
}
