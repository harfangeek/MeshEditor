#include "GUI\Core\GlutWindowManager.h"
#include "GUI\Core\GlutWindow.h"

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

Window* GlutWindowManager::GetWindow(int id)
{
	Window* window = NULL;

	if (windows.count(id) != 0)
		window = windows[id];

	return window;
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

	if (windows.count(id) == 0)
	{
		window = new GlutWindow(id, width, height, posX, posY, title);
		windows[id] = window;
		glutWindows[window->GetGlutId()] = window;
		glutDisplayFunc(GlutWindowManager::RenderWindow);
		glutReshapeFunc(GlutWindowManager::WindowReshape);
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
