#pragma once

#include "GUI\Interfaces\Window.h"
#include <string>

namespace GUI
{
	namespace Interfaces
	{
		class WindowManager
		{
		public:
			virtual GUI::Interfaces::Window* NewWindow(int id, int width, int height, int posX, int posY, std::string title) = 0;
			virtual GUI::Interfaces::Window* GetWindow(int id) = 0;

		protected:

		};
	}
}
