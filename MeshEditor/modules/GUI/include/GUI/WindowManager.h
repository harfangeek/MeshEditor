#pragma once

#include <string>
#include <map>

namespace GUI
{
	class Window;

	class WindowManager
	{
	public:
		virtual void Start();
		virtual void Terminate();
		virtual Window* NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, Window* sharedWindow = nullptr);
		virtual Window* GetWindow(unsigned int id);

	protected:
		virtual void DisplayWindows();

		std::map<unsigned int, Window*> windows;
	};
}
