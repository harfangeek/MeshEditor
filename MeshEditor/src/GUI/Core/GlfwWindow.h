#pragma once

#include "GUI/Interfaces/Window.h"
#include <string>

struct GLFWwindow;
struct ImGuiContext;
struct ImGlfwContext;

namespace GUI
{
	namespace Interfaces 
	{
		class Window;
	}

	namespace Core
	{
		class GlfwWindow : public GUI::Interfaces::Window
		{
		public:
			GLFWwindow* window;
			ImGuiContext* imguiContext;
			ImGlfwContext* glfwContext;

			GlfwWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, GlfwWindow* sharedWindow=nullptr);
			virtual ~GlfwWindow();

			// If you need to set custom GLFW callbacks on the window, do it before calling Init()
			virtual void Init();

			virtual void Resize(unsigned int width, unsigned int height);
			virtual void Move(int x, int y);
			virtual void SetTitle(std::string title);
			virtual void Display();
			
		protected:
			bool sharedGLContext;

			void SetWindow();

			void PreDisplay();
			void PostDisplay();
		};
	}
}