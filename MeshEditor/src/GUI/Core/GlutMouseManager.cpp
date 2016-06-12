#include "GUI\Core\GlutMouseManager.h"
#include "GUI\Model\MouseEvent.h"

using namespace GUI::Core;
using namespace GUI::Model;

GlutMouseManager::GlutMouseManager()
{
	x = 0;
	y = 0;
	oldX = 0;
	oldY = 0;
	for (int i = 0; i < NB_MOUSE_BUTTON; i++)
		buttons[i] = false;
}

GlutMouseManager::~GlutMouseManager()
{
}

void GlutMouseManager::MouseClick(MouseButton button, bool state, int x, int y)
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

void GlutMouseManager::MouseMotion(int x, int y)
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

void GlutMouseManager::MouseWheel(int wheel, int dir, int x, int y)
{
	this->wheel = wheel;

	MouseEvent event(MouseEvent::WHEEL);
	event.wheel = wheel;
	Notify(&event);
}

int GlutMouseManager::GetX()
{
	return x;
}

int GlutMouseManager::GetY()
{
	return y;
}

int GlutMouseManager::GetDX()
{
	return x - oldX;
}

int GlutMouseManager::GetDY()
{
	return y - oldY;
}

bool GlutMouseManager::GetButtonState(MouseButton button)
{
	return buttons[button];
}
