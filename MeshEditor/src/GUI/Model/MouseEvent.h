#pragma once

#include "GUI\Model\Event.h"
#include "GUI\Interfaces\Mouse.h"
#include "GUI\Interfaces\Window.h"

namespace GUI
{
	namespace Model
	{
		enum MouseMessage {
							 MOUSE_MOVE,
							 BUTTON_PRESSED,
							 BUTTON_RELEASED,
							 WHEEL_SCROLL
		};

		class MouseEvent : public Event
		{
		public:
			MouseEvent(GUI::Interfaces::Mouse* mouse, MouseMessage msg,
					   GUI::Interfaces::Window* window,
					   int x, int y, 
					   int dx, int dy, 
					   double sx, double sy, 
					   int wheel, GUI::Interfaces::MouseButton button);

			static MouseEvent MouseMove(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, int dx, int dy);
			static MouseEvent ButtonPressed(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, GUI::Interfaces::MouseButton button);
			static MouseEvent ButtonReleased(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, GUI::Interfaces::MouseButton button);
			static MouseEvent WheelScroll(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, int wheel);

			MouseMessage msg;
			GUI::Interfaces::Window* window;
			int x; // New position
			int y;
			int dx; // Movement in pixel
			int dy;
			double sx; // Speed in pixel/s
			double sy;
			int wheel; // > 1 => up, < -1 => down
			GUI::Interfaces::MouseButton button;
		};
	}
}