#pragma once

#include "GUI\Model\Event.h"
#include "GUI\Interfaces\IMouseManager.h"

namespace GUI
{
	namespace Model
	{
		enum MouseButton{ LEFT, RIGHT, MIDDLE };

		class MouseEvent : public Event
		{
		public:
			MouseEvent(int eventType);

			int x;
			int y;
			int dx;
			int dy;
			int wheel; // > 0 => up, < 0 => down
			GUI::Model::MouseButton button;

			static const int CLICK = 201; // Set x, y and button
			static const int MOVE = 202; // Set x, y, dx and dy
			static const int WHEEL = 203; // Set wheel
		};
	}
}