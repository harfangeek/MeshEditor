#pragma once

namespace GUI
{
	namespace Model
	{
		class Event
		{
		public:
			virtual ~Event();

			int type;
		};
	}
}