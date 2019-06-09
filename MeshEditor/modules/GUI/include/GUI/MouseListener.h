#pragma once

namespace GUI
{
	
	class Window;

	class MouseListener
	{
	public:
		virtual void OnMouseButtonEvent(GUI::Window* window, double x, double y, int button, int action, int mods) =0;
		virtual void OnMouseMoveEvent(GUI::Window* window, double x, double y, double dx, double dy) = 0;
		virtual void OnMouseScrollEvent(GUI::Window* window, double dx, double dy) = 0;
	};
}
