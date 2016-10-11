#include "GUI\Core\GlutWindowManager.h"
#include "GUI\Core\GlutWindow.h"
#include "GUI\Core\GlutMouse.h"

using namespace GUI::Core;
using namespace GUI::Interfaces;
using namespace std;

GlutWindowManager* GlutWindowManager::instance = NULL;

GlutWindowManager* GlutWindowManager::GetInstance()
{
	if (instance == NULL)
		instance = new GlutWindowManager();

	return instance;
}

GlutWindowManager::GlutWindowManager()
{
	mouse = GlutMouse::GetInstance();
}

GlutWindowManager::~GlutWindowManager()
{
	//for (map<int, GlutWindow*>::iterator it = windows.begin(); it != windows.end(); it++)
	//	delete (*it);
}

void GlutWindowManager::Init(int argc, char** argv, unsigned int displayMode)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(displayMode);
}

void GlutWindowManager::Display()
{
	glutMainLoop();
}

GlutWindow* GlutWindowManager::GetWindowFromGlutId(int glutId)
{
	GlutWindow* window = NULL;

	if (glutWindows.count(glutId) != 0)
		window = glutWindows[glutId];

	return window;
}

GlutWindow* GlutWindowManager::GetCurrentWindow()
{
	GlutWindow* window = NULL;
	int glutId = glutGetWindow();

	if (instance != NULL)
		window = instance->GetWindowFromGlutId(glutId);

	return window;
}

Window* GlutWindowManager::NewWindow(int id, int width, int height, int posX, int posY, string title)
{
	GlutWindow* window = NULL;
	
	window = new GlutWindow(id, width, height, posX, posY, title);
	if (window != NULL)
	{
		glutWindows[window->GetGlutId()] = window;
		
		glutDisplayFunc(GlutWindowManager::RenderWindow);
		glutReshapeFunc(GlutWindowManager::WindowReshape);
		
		glutMouseFunc(GlutWindowManager::MouseClick);
		glutPassiveMotionFunc(GlutWindowManager::MouseMove);
	}	

	return window;
}

void GlutWindowManager::RenderWindow()
{
	GlutWindow* window = GetCurrentWindow();
	if (window)
		window->Render();
}

void GlutWindowManager::WindowReshape(int width, int height)
{
	GlutWindow* window = GetCurrentWindow();
	if (window)
		window->Resize(width, height);
}

MouseButton GlutWindowManager::GetMouseButton(int glutButton)
{
	switch (glutButton)
	{
	case GLUT_RIGHT_BUTTON:
		return MouseButton::RIGHT_BUTTON;
	case GLUT_MIDDLE_BUTTON:
		return MouseButton::MIDDLE_BUTTON;
	default:
		return MouseButton::LEFT_BUTTON;
	}
}

void GlutWindowManager::MouseClick(int button, int state, int x, int y)
{
	GlutWindow* window = GetCurrentWindow();
	if (window && instance)
	{
		GlutMouse* mouse = (GlutMouse*)instance->GetMouse();
		if (mouse)
		{
			if (button == 3 || button == 4)
			{
				mouse->ScrollWheel(window->GetId(), button == 3 ? -1 : 1);
			}
			else
			{
				if (state == GLUT_DOWN)
					mouse->PressButton(window->GetId(), GetMouseButton(button));
				else if (state == GLUT_UP)
					mouse->ReleaseButton(window->GetId(), GetMouseButton(button));
			}
		}
	}
}

void GlutWindowManager::MouseMove(int x, int y)
{
	GlutWindow* window = GetCurrentWindow();
	if (window && instance)
	{
		GlutMouse* mouse = (GlutMouse*)instance->GetMouse();
		if (mouse)
			mouse->Move(window->GetId(), x, y);
	}
}

