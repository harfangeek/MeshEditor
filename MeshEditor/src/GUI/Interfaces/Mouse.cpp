#include "GUI\Interfaces\Mouse.h"
#include "GUI\Model\MouseEvent.h"

using namespace GUI::Interfaces;
using namespace GUI::Model;

Mouse::Mouse()
{
	x = 0;
	y = 0;
	lastMovement = time(NULL);
	for (int i = 0; i < 3; i++)
		buttons[i] = false;
}

Mouse::~Mouse()
{

}

int Mouse::GetX()
{
	return x;
}

int Mouse::GetY()
{
	return y;
}

bool Mouse::GetButtonState(MouseButton button)
{
	return buttons[button];
}

double Mouse::GetTimeSinceLastMovement()
{
	std::time_t currTime = time(NULL);
	return difftime(currTime, lastMovement);
}

void Mouse::Move(int windowId, int x, int y)
{
	int dx = x - this->x;
	int dy = y - this->y;
	this->x = x;
	this->y = y;
	MouseEvent event = MouseEvent::MouseMove(this, windowId, dx, dy);
	Notify(&event);
}

void Mouse::PressButton(int windowId, MouseButton button)
{
	buttons[button] = true;
	MouseEvent event = MouseEvent::ButtonPressed(this, windowId, button);
	Notify(&event);
}

void Mouse::ReleaseButton(int windowId, MouseButton button)
{
	buttons[button] = false;
	MouseEvent event = MouseEvent::ButtonPressed(this, windowId, button);
	Notify(&event);
}

void Mouse::ScrollWheel(int windowId, int value)
{
	MouseEvent event = MouseEvent::WheelScroll(this, windowId, value);
	Notify(&event);
}