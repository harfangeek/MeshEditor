#pragma once

#include <ctime>
#include "GUI\Interfaces\EventDispatcher.h"

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
			virtual bool GetButtonState(MouseButton button);
			virtual double GetTimeSinceLastMovement();
			
			virtual void Move(int windowId, int x, int y);
			virtual void PressButton(int windowId, MouseButton button);
			virtual void ReleaseButton(int windowId, MouseButton button);
			virtual void ScrollWheel(int windowId, int value);

		protected:

			int x;
			int y;
			bool buttons[3];
			std::time_t lastMovement;
		};
	}
}