#pragma once

#include "GUI/Interfaces/Window.h"

#include <string>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>

namespace GUI
{
	namespace Core
	{
		class GlfwWindow : public GUI::Interfaces::Window
		{
		public:
			GLFWwindow* window;
			ImGuiContext* imguiContext;

			GlfwWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, GlfwWindow* share);
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