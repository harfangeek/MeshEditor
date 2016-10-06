#pragma once

#include "GUI\Interfaces\EventDispatcher.h"
#include <ctime>
#include <string>

namespace GUI
{
	namespace Interfaces
	{
		class Window : public GUI::Interfaces::EventDispatcher
		{
		public:
			Window(int id, int width, int height, int x, int y, std::string title="");
			virtual ~Window();

			virtual void Resize(int width, int height);
			virtual void Move(int x, int y);
			virtual void SetTitle(std::string title);
			virtual void Render();

			int GetId();
			int GetWidth();
			int GetHeight();
			int GetX();
			int GetY();
			std::string GetTitle();
			double GetTimeSinceLastFrame();

		protected:
			int id;
			int width;
			int height;
			int x;
			int y;
			float lastRender;
			std::string title;
			std::time_t lastFrame;
		};
	}
}
