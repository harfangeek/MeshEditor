#include "GUI/WindowManager.h"
#include "GUI/Window.h"

using namespace GUI;

void WindowManager::Start()
{
}

void WindowManager::Terminate()
{
}

Window* WindowManager::NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, Window* sharedWindow)
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
