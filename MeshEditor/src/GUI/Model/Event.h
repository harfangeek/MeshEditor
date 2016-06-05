#pragma once

namespace GUI
{
	namespace Model
	{
		class Event
		{
		public:
			Event(int eventType);
			virtual ~Event();

			int type;
		};
	}
}