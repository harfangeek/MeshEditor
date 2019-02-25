#pragma once

#include "GUI/Interfaces/Window.h"

#include <string>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

namespace GUI
{
	namespace Core
	{
		class GlfwWindow : public GUI::Interfaces::Window
		{
		public:
			GLFWwindow* window;

			GlfwWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title);
			virtual ~GlfwWindow();

			virtual void Resize(unsigned int width, unsigned int height);
			virtual void Move(int x, int y);
			virtual void SetTitle(std::string title);
			virtual void Display();
			
		protected:
			void SetWindow();

			void PreDisplay();
			void PostDisplay();
		};
	}
}