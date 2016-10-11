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
		instance = new GlutMouse();

	return instance;
}
GlutMouse::GlutMouse()
{

}

GlutMouse::~GlutMouse()
{

}

void GlutMouse::Move(int windowId, int x, int y)
{
	//glutWarpPointer()
	Mouse::Move(windowId, x, y);
}
