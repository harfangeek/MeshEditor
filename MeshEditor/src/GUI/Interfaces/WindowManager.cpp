#include "GUI/Interfaces/WindowManager.h"

using namespace GUI::Interfaces;

void WindowManager::Start()
{
}

void WindowManager::Terminate()
{
}

GUI::Interfaces::Window* WindowManager::NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title)
{
	Window* window = NULL;

	if (windows.count(id) == 0)
	{
		window = new Window(id, width, height, posX, posY, title);
		windows[id] = window;
	}

	return window;
}

void WindowManager::DisplayWindows()
{
	for (auto window : windows)
		window.second->Display();
}

Window* WindowManager::GetWindow(unsigned int id)
{
	Window* window = NULL;

	if (windows.count(id) != 0)
		window = windows[id];

	return window;
}
