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
			virtual Window* NewWindow(int width, int height, int posX, int posY, std::string title) = 0;

		protected:

		};
	}
}
