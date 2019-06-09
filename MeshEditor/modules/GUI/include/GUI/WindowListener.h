#pragma once

namespace GUI
{
	class Window;

	class WindowListener
	{
	public:
		virtual void OnWindowResizedEvent(Window* window, int width, int height) =0;
	};
}
