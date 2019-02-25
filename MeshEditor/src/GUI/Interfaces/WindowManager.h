#pragma once

#include "GUI/Interfaces/Window.h"

#include <string>
#include <map>

namespace GUI
{
	namespace Interfaces
	{
		class WindowManager
		{
		public:
			virtual void Start();
			virtual void Terminate();
			virtual GUI::Interfaces::Window* NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title);
			virtual GUI::Interfaces::Window* GetWindow(unsigned int id);

		protected:
			virtual void DisplayWindows();

			std::map<unsigned int, GUI::Interfaces::Window*> windows;
		};
	}
}
