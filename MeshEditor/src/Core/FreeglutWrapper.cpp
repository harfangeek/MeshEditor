#include "Core\FreeglutWrapper.h"
#include "Core\WindowManager.h"
#include "Model\StaticData.h"
#include "Dependencies\freeglut\freeglut.h"

void StartGlut()
{
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	glutDisplayFunc(RenderWindow);
	glutMainLoop();
}

void MouseClick(int button, int state, int x, int y)
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->MouseClick(button, state, x, y);
}

void MouseMotion(int x, int y)
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->MouseMotion(x, y);
}

void RenderWindow()
{
	Core::WindowManager* windowManager = Model::StaticData::GetWindowManager();
	if (windowManager)
		windowManager->Render();
}