#pragma once

#include "GUI\Interfaces\Window.h"
#include "GUI\Interfaces\Mouse.h"
#include <string>
#include <map>

namespace GUI
{
	namespace Interfaces
	{
		class WindowManager
		{
		public:
			virtual GUI::Interfaces::Window* NewWindow(int id, int width, int height, int posX, int posY, std::string title);
			virtual GUI::Interfaces::Window* GetWindow(int id);
			virtual GUI::Interfaces::Mouse* GetMouse();

		protected:
			std::map<int, GUI::Interfaces::Window*> windows;
			GUI::Interfaces::Mouse* mouse;
		};
	}
}
