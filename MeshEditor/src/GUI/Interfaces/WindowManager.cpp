#include "GUI\Interfaces\WindowManager.h"

using namespace GUI::Interfaces;

GUI::Interfaces::Window* WindowManager::NewWindow(int id, int width, int height, int posX, int posY, std::string title)
{
	Window* window = NULL;

	if (windows.count(id) == 0)
	{
		window = new Window(id, width, height, posX, posY, title);
		windows[id] = window;
	}

	return window;
}

GUI::Interfaces::Mouse* WindowManager::GetMouse()
{
	return mouse;
}

Window* WindowManager::GetWindow(int id)
{
	Window* window = NULL;

	if (windows.count(id) != 0)
		window = windows[id];

	return window;
}