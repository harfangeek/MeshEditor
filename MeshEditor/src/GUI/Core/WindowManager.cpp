#include "GUI\Core\WindowManager.h"
#include "Dependencies\freeglut\freeglut.h"

using namespace GUI::Core;
using namespace Rendering::Core;

WindowManager::WindowManager()
{
	for(int i = 0 ; i < NB_MOUSE_BUTTON ; i++)
		mouseButtons[i] = false;
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

void WindowManager::MouseClick(MouseButton button, bool state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	mouseButtons[button] = state;
}

void WindowManager::MouseMotion(int x, int y)
{
	float dx = (float)(x - mouseX);
	float dy = (float)(y - mouseY);
	mouseX = x;
	mouseY = y;
	float vx = dx / (float)width;
	float vy = dy / (float)height;

	if(mouseButtons[MouseButton::LEFT])
		meshRenderer->Rotate(vx, vy);
	else if(mouseButtons[MouseButton::MIDDLE])
		meshRenderer->Translate(-vx, vy);
	glutPostRedisplay();
}

void WindowManager::MouseWheel(int wheel, int dir, int x, int y)
{
	meshRenderer->Zoom(dir > 0 ? 0.1f : -0.1f);
	glutPostRedisplay();
}

void WindowManager::Reshape(int width, int height)
{
	meshRenderer->SetViewPort(width, height);
}
