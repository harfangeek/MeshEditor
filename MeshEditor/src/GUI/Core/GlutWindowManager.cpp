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

Window* GlutWindowManager::NewWindow(int width, int height, int posX, int posY, string title)
{
	GlutWindow* window = new GlutWindow(width, height, posX, posY, title);

	return window;
}
