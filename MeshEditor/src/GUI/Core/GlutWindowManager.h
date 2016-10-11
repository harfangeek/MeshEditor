#pragma once

#include "GUI\Interfaces\WindowManager.h"
#include "GUI\Interfaces\Window.h"
#include "GUI\Interfaces\Mouse.h"
#include "Dependencies\freeglut\include\freeglut.h"
#include <map>
#include <string>

namespace GUI
{
	namespace Core
	{
		class GlutWindow;

		class GlutWindowManager : public GUI::Interfaces::WindowManager
		{
		public:
			static GUI::Core::GlutWindowManager* GetInstance();
			virtual ~GlutWindowManager();

			void Init(int argc, char** argv, unsigned int displayMode = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
			virtual GUI::Interfaces::Window* NewWindow(int id, int width, int height, int posX, int posY, std::string title);
			
			GUI::Core::GlutWindow* GetWindowFromGlutId(int glutId);
			void Display();
			
		private:
			GlutWindowManager();

			static GlutWindow* GetCurrentWindow();
			static void RenderWindow();
			static void WindowReshape(int width, int height);
			static GUI::Interfaces::MouseButton GetMouseButton(int glutButton);
			static void MouseClick(int button, int state, int x, int y);
			static void MouseMove(int x, int y);

			static GUI::Core::GlutWindowManager* instance;
			
			std::map<int, GUI::Core::GlutWindow*> glutWindows;
		};
	}
}