#include "Core\WindowManager.h"
#include "Dependencies\freeglut\freeglut.h"

using namespace Core;

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

void WindowManager::MouseClick(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void WindowManager::MouseMotion(int x, int y)
{
	float dx = (float)(x - mouseX);
	float dy = (float)(y - mouseY);
	mouseX = x;
	mouseY = y;
	float vx = dx / (float)width;
	float vy = dy / (float)height;

	meshRenderer->Rotate(vx, vy);
	glutPostRedisplay();
}

void WindowManager::MouseWheel(int button, int dir, int x, int y)
{
	meshRenderer->Zoom(dir > 0 ? 0.1 : -0.1);
	glutPostRedisplay();
}

void WindowManager::Reshape(int width, int height)
{
	meshRenderer->SetViewPort(width, height);
	//meshRenderer->Display();
}
