#pragma once

namespace GUI
{
	namespace Interfaces
	{
		class Window;

		class MouseListener
		{
		public:
			virtual void OnMouseButtonEvent(GUI::Interfaces::Window* window, double x, double y, int button, int action, int mods) =0;
			virtual void OnMouseMoveEvent(GUI::Interfaces::Window* window, double x, double y, double dx, double dy) = 0;
			virtual void OnMouseScrollEvent(GUI::Interfaces::Window* window, double dx, double dy) = 0;
		};
	}
}