#pragma once

#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		enum MouseButton{
			LEFT,
			RIGHT,
			MIDDLE
		};

		class Mouse
		{
		public:
			virtual int GetX() = 0;
			virtual int GetY() = 0;
			virtual int GetDX() = 0;
			virtual int GetDY() = 0;
			virtual bool GetButtonState(MouseButton button) = 0;
		};
	}
}