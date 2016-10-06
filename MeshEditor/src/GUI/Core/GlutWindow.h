#pragma once

#include "GUI\Interfaces\Window.h"
#include "GUI\Core\GlutWindowManager.h"
#include <map>
#include <string>

namespace GUI
{
	namespace Core
	{
		class GlutWindow : public GUI::Interfaces::Window
		{
		public:
			GlutWindow(int id, int width, int height, int posX, int posY, std::string title);
			virtual ~GlutWindow();

			virtual void Resize(int width, int height);
			virtual void Move(int x, int y);
			virtual void SetTitle(std::string title);
			virtual void Render();
			virtual int GetGlutId();

		protected:
			int glutId;

			void SetWindow();
		};
	}
}