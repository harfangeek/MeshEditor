#pragma once

namespace GUI
{
	namespace Interfaces
	{
		class Window;

		class WindowListener
		{
		public:
			virtual void OnWindowResizedEvent(GUI::Interfaces::Window* window, int width, int height) =0;
		};
	}
}