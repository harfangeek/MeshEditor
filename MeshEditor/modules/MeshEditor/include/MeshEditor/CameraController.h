#pragma once

#include "GUI/MouseListener.h"
#include "GUI/WindowListener.h"

namespace Rendering
{
	class MeshRenderer;
}

namespace MeshEditor
{
	class CameraController : public GUI::MouseListener,
							 public GUI::WindowListener
	{
	public:
		CameraController(Rendering::MeshRenderer* meshRenderer);
		virtual ~CameraController();

		virtual void OnMouseButtonEvent(GUI::Window* window, double x, double y, int button, int action, int mods);
		virtual void OnMouseMoveEvent(GUI::Window* window, double x, double y, double dx, double dy);
		virtual void OnMouseScrollEvent(GUI::Window* window, double dx, double dy);
		virtual void OnWindowResizedEvent(GUI::Window* window, int width, int height);

	private:
		bool translate;
		bool rotate;
		Rendering::MeshRenderer* meshRenderer;
	};
}
