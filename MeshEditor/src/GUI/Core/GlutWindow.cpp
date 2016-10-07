#include "Dependencies\freeglut\include\freeglut.h"
#include <iostream>

#include "GUI\Core\GlutWindow.h"

using namespace GUI::Core;
using namespace std;

GlutWindow::GlutWindow(int id, int width, int height, int x, int y, string title) : Window(id, width, height, x, y, title)
{
	glutId = glutCreateWindow(title.c_str());
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
}

GlutWindow::~GlutWindow()
{

}

int GlutWindow::GetGlutId()
{
	return glutId;
}

void GlutWindow::SetWindow()
{
	glutSetWindow(glutId);
}

void GlutWindow::Resize(int width, int height)
{	
	SetWindow();
	glutInitWindowSize(width, height);
	Window::Resize(width, height);
}

void GlutWindow::Move(int x, int y)
{
	SetWindow();
	glutInitWindowPosition(x, y);
	Window::Move(x, y);
}

void GlutWindow::SetTitle(std::string title)
{
	SetWindow();
	glutSetWindowTitle(title.c_str());
	Window::SetTitle(title);
}

void GlutWindow::Render()
{
	SetWindow();
	Window::Render();
	glutSwapBuffers();
}
