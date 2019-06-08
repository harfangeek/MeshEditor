#pragma once

#include "GUI/WindowManager.h"
#include <string>

struct GLFWwindow;

namespace GUI
{
	class Window;
	class GlfwWindow;

	class GlfwWindowManager : public GUI::WindowManager
	{
	public:
		static GlfwWindowManager* GetInstance();
		virtual ~GlfwWindowManager();

		static void Init();
			
		virtual Window* NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, std::string title, Window* sharedWindow=nullptr);

		virtual void Start();			
		virtual void Terminate();

	protected:
		GlfwWindowManager();

		GlfwWindow* FindGLFWWindow(GLFWwindow* window);

		static void ErrorCallback(int error, const char* description);
		static void MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow* glfwWindow, double x, double y);
		static void MouseScrollCallback(GLFWwindow* glfwWindow, double dx, double dy);
		static void WindowResizedCallback(GLFWwindow* glfwWindow, int width, int height);

		static GlfwWindowManager* instance;
		static bool initialized;
	};
}
