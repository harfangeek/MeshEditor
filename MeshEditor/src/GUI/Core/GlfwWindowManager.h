#pragma once

#include "GUI/Interfaces/WindowManager.h"
#include <string>

struct GLFWwindow;

namespace GUI
{
	namespace Interfaces
	{
		class Window;
	}

	namespace Core
	{
		class GlfwWindow;

		class GlfwWindowManager : public GUI::Interfaces::WindowManager
		{
		public:
			static GUI::Core::GlfwWindowManager* GetInstance();
			virtual ~GlfwWindowManager();

			static void Init();
			
			virtual GUI::Interfaces::Window* NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, GUI::Interfaces::Window* sharedWindow=nullptr);

			virtual void Start();			
			virtual void Terminate();

		protected:
			GlfwWindowManager();

			GUI::Core::GlfwWindow* FindGLFWWindow(GLFWwindow* window);

			static void ErrorCallback(int error, const char* description);
			static void MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
			static void MouseMoveCallback(GLFWwindow* glfwWindow, double x, double y);
			static void MouseScrollCallback(GLFWwindow* glfwWindow, double dx, double dy);
			static void WindowResizedCallback(GLFWwindow* glfwWindow, int width, int height);

			static GUI::Core::GlfwWindowManager* instance;
			static bool initialized;
		};
	}
}