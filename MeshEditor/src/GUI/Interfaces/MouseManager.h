#pragma once

#include <vector>

namespace GUI
{
	namespace Model { enum MouseButton; }

	namespace Interfaces
	{
		class MouseManager
		{
		public:
			virtual int GetX() = 0;
			virtual int GetY() = 0;
			virtual int GetDX() = 0;
			virtual int GetDY() = 0;
			virtual bool GetButtonState(GUI::Model::MouseButton button) = 0;
		};
	}
}