#pragma once

#include "GUI\Interfaces\Mouse.h"
#include "GUI\Interfaces\EventDispatcher.h"
#include "GUI\Model\MouseEvent.h"

#define NB_MOUSE_BUTTON 3

namespace GUI
{
	namespace Core
	{
		class GlutMouse : public GUI::Interfaces::Mouse, 
						  public GUI::Interfaces::EventDispatcher
		{
		private:
			
			static void OnClick(int button, int state, int x, int y);

			GlutMouse();
			~GlutMouse();

			static GlutMouse* instance;
			int x;
			int y;
			int dX;
			int dY;
			int wheel;
			bool buttons[NB_MOUSE_BUTTON];

		public:

			static GlutMouse* GetInstance();
			static void Free();

			void MouseClick(int button, int state, int x, int y);
			void MouseMotion(int x, int y);
			void MouseWheel(int wheel, int dir, int x, int y);

			virtual int GetX();
			virtual int GetY();
			virtual int GetDX();
			virtual int GetDY();
			virtual bool GetButtonState(GUI::Interfaces::MouseButton button);
		};
	}
}