#pragma once

#include "GUI\Interfaces\MouseManager.h"
#include "GUI\Interfaces\EventDispatcher.h"
#include "GUI\Model\MouseEvent.h"

#define NB_MOUSE_BUTTON 3

namespace GUI
{
	namespace Model { enum MouseButton; }

	namespace Core
	{
		class GlutMouseManager : public GUI::Interfaces::MouseManager, 
							 public GUI::Interfaces::EventDispatcher
		{
		private:
			int x;
			int y;
			int oldX;
			int oldY;
			int wheel;
			bool buttons[NB_MOUSE_BUTTON];

		public:
			GlutMouseManager();
			~GlutMouseManager();

			void MouseClick(GUI::Model::MouseButton button, bool state, int x, int y);
			void MouseMotion(int x, int y);
			void MouseWheel(int wheel, int dir, int x, int y);

			virtual int GetX();
			virtual int GetY();
			virtual int GetDX();
			virtual int GetDY();
			virtual bool GetButtonState(GUI::Model::MouseButton button);
		};
	}
}