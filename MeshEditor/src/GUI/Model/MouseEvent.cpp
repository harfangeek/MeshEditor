#include "GUI\Model\MouseEvent.h"

using namespace GUI::Model;
using namespace GUI::Interfaces;

MouseEvent::MouseEvent(GUI::Interfaces::Mouse* mouse, MouseMessage msg,
					   GUI::Interfaces::Window* window,
					   int x, int y,
					   int dx, int dy,
					   double sx, double sy,
					   int wheel, GUI::Interfaces::MouseButton button) : Event(mouse, MessageType::MOUSE), msg(msg),
																		 window(window),
																		 x(x), y(y),
																		 dx(dx), dy(dy),
																		 sx(sx), sy(sx),
																		 wheel(wheel), button(button)
{

}

MouseEvent MouseEvent::MouseMove(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, int dx, int dy)
{
	double t = mouse->GetTimeSinceLastMovement();
	double sx = (double)dx / t;
	double sy = (double)dy / t;
	return MouseEvent(mouse, MouseMessage::MOUSE_MOVE, window, mouse->GetX(), mouse->GetY(), dx, dy, sx, sy, 0, (MouseButton)0);
}

MouseEvent MouseEvent::ButtonPressed(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, GUI::Interfaces::MouseButton button)
{
	return MouseEvent(mouse, MouseMessage::BUTTON_PRESSED, window, mouse->GetX(), mouse->GetY(), 0, 0, 0, 0, 0, button);
}

MouseEvent MouseEvent::ButtonReleased(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, GUI::Interfaces::MouseButton button)
{
	return MouseEvent(mouse, MouseMessage::BUTTON_RELEASED, window, mouse->GetX(), mouse->GetY(), 0, 0, 0, 0, 0, button);
}

MouseEvent MouseEvent::WheelScroll(GUI::Interfaces::Mouse* mouse, GUI::Interfaces::Window* window, int wheel)
{
	return MouseEvent(mouse, MouseMessage::WHEEL_SCROLL, window, mouse->GetX(), mouse->GetY(), 0, 0, 0, 0, wheel, (MouseButton)0);
}
