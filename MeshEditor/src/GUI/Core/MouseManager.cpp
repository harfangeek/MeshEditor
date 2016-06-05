#include "GUI\Core\MouseManager.h"
#include "GUI\Model\MouseEvent.h"

using namespace GUI::Core;
using namespace GUI::Model;

MouseManager::MouseManager()
{
	x = 0;
	y = 0;
	oldX = 0;
	oldY = 0;
	for (int i = 0; i < NB_MOUSE_BUTTON; i++)
		buttons[i] = false;
}

MouseManager::~MouseManager()
{
}

void MouseManager::MouseClick(MouseButton button, bool state, int x, int y)
{
	oldX = x;
	oldY = y;
	this->x = x;
	this->y = y;

	MouseEvent event(MouseEvent::CLICK);
	event.x = x;
	event.y = y;
	Notify(&event);
}

void MouseManager::MouseMotion(int x, int y)
{
	oldX = x;
	oldY = y;
	this->x = x;
	this->y = y;

	MouseEvent event(MouseEvent::MOVE);
	event.x = x;
	event.y = y;
	event.dx = GetDX();
	event.dy = GetDY();
	Notify(&event);
}

void MouseManager::MouseWheel(int wheel, int dir, int x, int y)
{
	this->wheel = wheel;

	MouseEvent event(MouseEvent::WHEEL);
	event.wheel = wheel;
	Notify(&event);
}

int MouseManager::GetX()
{
	return x;
}

int MouseManager::GetY()
{
	return y;
}

int MouseManager::GetDX()
{
	return x - oldX;
}

int MouseManager::GetDY()
{
	return y - oldY;
}

bool MouseManager::GetButtonState(MouseButton button)
{
	return buttons[button];
}
