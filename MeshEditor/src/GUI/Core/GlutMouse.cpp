#include "GUI\Core\GlutMouse.h"
#include "GUI\Model\MouseEvent.h"
#include "Dependencies\freeglut\include\freeglut.h"

#include <iostream>

using namespace GUI::Core;
using namespace GUI::Model;
using namespace GUI::Interfaces;

GlutMouse* GlutMouse::instance = NULL;

GlutMouse* GlutMouse::GetInstance()
{
	if (instance == NULL)
	{
		instance = new GlutMouse();
		glutMouseFunc(GlutMouse::OnClick);
	}

	return instance;
}

void GlutMouse::Free()
{
	if (instance)
	{
		delete instance;
		instance = NULL;
	}
}

void GlutMouse::OnClick(int button, int state, int x, int y)
{
	if (instance)
		instance->MouseClick(button, state, x, y);
}

GlutMouse::GlutMouse()
{
	x = 0;
	y = 0;
	dX = 0;
	dY = 0;
	for (int i = 0; i < NB_MOUSE_BUTTON; i++)
		buttons[i] = false;
}

GlutMouse::~GlutMouse()
{
}

void GlutMouse::MouseClick(int, int state, int x, int y)
{
	dX = x - this->x;
	dY = x - this->y;
	this->x = x;
	this->y = y;

	std::cout << x << " : " << y << std::endl;

	/*MouseEvent event(MouseEvent::);
	event.x = x;
	event.y = y;
	Notify(&event);*/
}

void GlutMouse::MouseMotion(int x, int y)
{
	dX = x - this->x;
	dY = x - this->y;
	this->x = x;
	this->y = y;

	/*MouseEvent event(MouseEvent::MOVE);
	event.x = x;
	event.y = y;
	event.dx = GetDX();
	event.dy = GetDY();
	Notify(&event);*/
}

void GlutMouse::MouseWheel(int wheel, int dir, int x, int y)
{
	this->wheel = wheel;

	/*MouseEvent event(MouseEvent::WHEEL);
	event.wheel = wheel;
	Notify(&event);*/
}

int GlutMouse::GetX()
{
	return x;
}

int GlutMouse::GetY()
{
	return y;
}

int GlutMouse::GetDX()
{
	return dX;
}

int GlutMouse::GetDY()
{
	return dY;
}

bool GlutMouse::GetButtonState(MouseButton button)
{
	return buttons[button];
}
