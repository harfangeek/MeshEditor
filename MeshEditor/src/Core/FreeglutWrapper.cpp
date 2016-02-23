#include "Core\FreeglutWrapper.h"
#include "Core\WindowManager.h"
#include "Model\StaticData.h"
#include "Dependencies\freeglut\freeglut.h"

using namespace Core;

void StartGlut()
{
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(RenderWindow);
	glutReshapeFunc(WindowReshape);
	glutMainLoop();
}

void MouseClick(int button, int state, int x, int y)
{
	MouseButton mouseButton = button == GLUT_LEFT_BUTTON ? MouseButton::LEFT :
							  (button == GLUT_MIDDLE_BUTTON ? MouseButton::MIDDLE : MouseButton::RIGHT);
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->MouseClick(mouseButton, state == 0, x, y);
}

void MouseMotion(int x, int y)
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->MouseMotion(x, y);
}

void MouseWheel(int button, int dir, int x, int y)
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->MouseWheel(button, dir, x, y);
}

void WindowReshape(int width, int height)
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->Reshape(width, height);
}


void RenderWindow()
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->Render();
}