#pragma once

#include "GUI\Model\Event.h"

namespace GUI
{
	namespace Model
	{
		class WindowEvent : public Event
		{
		public:
			WindowEvent(int eventType);

			int width;
			int height;

			static const int RESHAPE = 101;
			static const int RENDER = 102;
		};
	}
}