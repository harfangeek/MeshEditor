#include "GUI\Core\WindowManager.h"
#include "Dependencies\freeglut\include\freeglut.h"

using namespace GUI::Core;
using namespace Rendering::Core;

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{

}

void WindowManager::Init(int width, int height, int argc, char** argv)
{
	this->width = width;
	this->height = height;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(width, height);
	glutCreateWindow("Title");
}

void WindowManager::SetMeshRenderer(MeshRenderer* meshRenderer)
{
	this->meshRenderer = meshRenderer;
}

MeshRenderer* WindowManager::GetMeshRenderer()
{
	return meshRenderer;
}

void WindowManager::Render()
{
	if (meshRenderer)
	{
		meshRenderer->Display();
		glutSwapBuffers();
	}
}

void WindowManager::Reshape(int width, int height)
{
	meshRenderer->SetViewPort(width, height);
}
