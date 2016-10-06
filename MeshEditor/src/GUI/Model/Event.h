#pragma once

namespace GUI
{
	namespace Interfaces {
		class EventDispatcher;
	}

	namespace Model
	{
		enum MessageType { WINDOW, MOUSE, KEYBOARD };

		class Event
		{
		public:
			Event(GUI::Interfaces::EventDispatcher* src, MessageType eventType);
			virtual ~Event();

			GUI::Interfaces::EventDispatcher* src;
			MessageType msgType;
		};
	}
}