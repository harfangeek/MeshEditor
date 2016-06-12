#include "GUI\Core\GlutWindow.h"
#include "Dependencies\freeglut\include\freeglut.h"

#include <iostream>

using namespace GUI::Core;
//using namespace Rendering::Core;
using namespace std;

/*void Reshape2(int width, int height)
{
	std::cout << glutGetWindow() << " : " << width << " / " << height << std::endl;
}

void GlutWindow::MouseClick3(int button, int state, int x, int y)
{
	std::cout << glutGetWindow() << " : " << x << " / " << y << std::endl;
}*/

GlutWindow::GlutWindow(int width, int height, int posX, int posY, string title)
{
	this->width = width;
	this->height = height;
	x = posX;
	y = posY;
	this->title = title;
	//meshRenderer = NULL;

	CreateGlutWindow();
}

GlutWindow::~GlutWindow()
{

}

void GlutWindow::CreateGlutWindow()
{
	id = glutCreateWindow(title.c_str());
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);

	//(MouseClick3);
}

/*void GlutWindow::Reshape(int width, int height)
{
	std::cout << glutGetWindow() << " : " << width << " / " << height << std::endl;
}*/

/*void GlutWindow::SetMeshRenderer(MeshRenderer* meshRenderer)
{
	this->meshRenderer = meshRenderer;
}

MeshRenderer* GlutWindow::GetMeshRenderer()
{
	return meshRenderer;
}

void GlutWindow::Render()
{
	if (meshRenderer)
	{
		meshRenderer->Display();
		glutSwapBuffers();
	}
}

void GlutWindow::Reshape(int width, int height)
{
	if (meshRenderer)
		meshRenderer->SetViewPort(width, height);
}*/
