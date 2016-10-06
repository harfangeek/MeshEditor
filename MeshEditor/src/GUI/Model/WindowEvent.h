#pragma once

#include "GUI\Model\Event.h"
#include "GUI\Interfaces\Window.h"

namespace GUI
{
	namespace Model
	{
		enum WindowMessages {
			WINDOW_RESIZED,
			WINDOW_RENDERED
		};

		class WindowEvent : public Event
		{
		public:
			WindowEvent(GUI::Interfaces::Window* window, WindowMessages msg);

			WindowMessages msg;
			int windowId;
			int width;
			int height;
			int prevWidth;
			int prevHeight;
			double timeSinceLastFrame;
		};
	}
}