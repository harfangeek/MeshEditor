#pragma once

#include <ctime>
#include "GUI\Interfaces\EventDispatcher.h"
#include "GUI\Interfaces\Window.h"

namespace GUI
{
	namespace Interfaces
	{
		enum MouseButton{
			LEFT_BUTTON = 0,
			RIGHT_BUTTON,
			MIDDLE_BUTTON
		};

		class Mouse : public EventDispatcher
		{
		public:
			Mouse();
			virtual ~Mouse();
			virtual int GetX();
			virtual int GetY();
			virtual bool IsButtonPressed(MouseButton button);
			virtual double GetTimeSinceLastMovement();
			
			virtual void Move(GUI::Interfaces::Window* window, int x, int y);
			virtual void PressButton(GUI::Interfaces::Window* window, MouseButton button);
			virtual void ReleaseButton(GUI::Interfaces::Window* window, MouseButton button);
			virtual void ScrollWheel(GUI::Interfaces::Window* window, int value);

		protected:

			int x;
			int y;
			bool buttons[3];
			std::time_t lastMovement;
		};
	}
}