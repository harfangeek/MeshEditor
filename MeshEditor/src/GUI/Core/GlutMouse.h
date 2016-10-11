#pragma once

#include "GUI\Interfaces\Mouse.h"

#define NB_MOUSE_BUTTON 3

namespace GUI
{
	namespace Core
	{
		class GlutMouse : public GUI::Interfaces::Mouse
		{
		public:
			static GlutMouse* GetInstance();
			virtual ~GlutMouse();

			virtual void Move(GUI::Interfaces::Window* window, int x, int y);

		private:
			GlutMouse();

			static GlutMouse* instance;
		};
	}
}