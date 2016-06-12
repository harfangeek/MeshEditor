#pragma once

#include "GUI\Interfaces\WindowManager.h"
#include "GUI\Interfaces\Window.h"
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

			void Init(int argc, char** argv, unsigned int displayMode = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
			virtual GUI::Interfaces::Window* NewWindow(int width, int height, int posX, int posY, std::string title);
			void Display();
			
		private:
			GlutWindowManager();
			virtual ~GlutWindowManager();

			static GUI::Core::GlutWindowManager* instance;
			std::map<int, GUI::Core::GlutWindow*> windows;
		};
	}
}