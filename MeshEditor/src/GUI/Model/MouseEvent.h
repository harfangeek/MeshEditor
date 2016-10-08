#pragma once

#include "GUI\Model\Event.h"
#include "GUI\Interfaces\Mouse.h"

namespace GUI
{
	namespace Model
	{
		enum MouseMessages { LEFT_BUTTON_PRESSED, 
							 LEFT_BUTTON_RELEASED,
							 RIGHT_BUTTON_PRESSED,
							 RIGHT_BUTTON_RELEASED,
							 MIDDLE_BUTTON_PRESSED,
							 MIDDLE_BUTTON_RELEASED,
							 WHEEL_SCROLL,
							 MOUSE_MOVE};

		class MouseEvent : public Event
		{
		public:
			MouseEvent(MouseMessages msg);

			MouseMessages msg;
			int x;
			int y;
			int dx;
			int dy;
			int wheel; // > 0 => up, < 0 => down
			GUI::Interfaces::MouseButton button;
		};
	}
}