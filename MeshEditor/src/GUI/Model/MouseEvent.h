#pragma once

#include "GUI\Model\Event.h"
#include "GUI\Interfaces\Mouse.h"

namespace GUI
{
	namespace Model
	{
		enum MouseMessage {
							 MOUSE_MOVE,
							 MOUSE_DRAG,
							 BUTTON_PRESSED,
							 BUTTON_RELEASED,
							 WHEEL_SCROLL
		};

		class MouseEvent : public Event
		{
		public:
			MouseEvent(GUI::Interfaces::Mouse* mouse, MouseMessage msg,
					   int windowId,
					   int x, int y, 
					   int dx, int dy, 
					   double sx, double sy, 
					   int wheel, GUI::Interfaces::MouseButton button);

			static MouseEvent MouseMove(GUI::Interfaces::Mouse* mouse, int windowId, int dx, int dy);
			static MouseEvent ButtonPressed(GUI::Interfaces::Mouse* mouse, int windowId, GUI::Interfaces::MouseButton button);
			static MouseEvent ButtonReleased(GUI::Interfaces::Mouse* mouse, int windowId, GUI::Interfaces::MouseButton button);
			static MouseEvent WheelScroll(GUI::Interfaces::Mouse* mouse, int windowId, int wheel);

			MouseMessage msg;
			int windowId;
			int x; // New position
			int y;
			int dx; // Movement in pixel
			int dy;
			double sx; // Speed in pixel/s
			double sy;
			int wheel; // > 0 => up, < 0 => down
			GUI::Interfaces::MouseButton button;
		};
	}
}