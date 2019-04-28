#include "GUI/Core/GlfwWindowManager.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

using namespace GUI::Core;
using namespace GUI::Interfaces;
using namespace std;

GlfwWindowManager* GlfwWindowManager::instance = NULL;
bool GlfwWindowManager::initialized = false;

GlfwWindowManager* GlfwWindowManager::GetInstance()
{
	if (instance == NULL)
		instance = new GlfwWindowManager();

	if (!initialized)
		Init();

	return instance;
}

GlfwWindowManager::GlfwWindowManager()
{
}

GlfwWindowManager::~GlfwWindowManager()
{
	Terminate();
}

void GlfwWindowManager::Init()
{
	// Init GLFW
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
		return ;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// Init IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();	
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	initialized = true;
}

void GlfwWindowManager::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	for (auto pair : windows)
	{
		if (pair.second != NULL)
		{
			GlfwWindow* window = dynamic_cast<GlfwWindow*>(pair.second);
			if (window)
			{
				glfwDestroyWindow(window->window);
				delete window;
			}
		}
	}

	glfwTerminate();
}

void  GlfwWindowManager::ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void  GlfwWindowManager::Start()
{
	auto it = windows.begin();
	if (it != windows.end())
	{
		auto mainWindow = dynamic_cast<GlfwWindow*>(it->second);
		if(mainWindow)
			while (!glfwWindowShouldClose(mainWindow->window))
				DisplayWindows();
	}
}

Window* GlfwWindowManager::NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, string title)
{
	GlfwWindow* share = NULL;
	auto e = windows.begin();
	if (e != windows.end())
		share = dynamic_cast<GlfwWindow*>(e->second);

	// Create window with graphics context
	GlfwWindow* window = new GlfwWindow(id, width, height, posX, posY, title, share);

	if (window && window->window)
	{
		windows[id] = window;

		glfwSetMouseButtonCallback(window->window, GlfwWindowManager::MouseButtonCallback);
		glfwSetCursorPosCallback(window->window, GlfwWindowManager::MouseMoveCallback);
		glfwSetScrollCallback(window->window, GlfwWindowManager::MouseScrollCallback);
		glfwSetWindowSizeCallback(window->window, GlfwWindowManager::WindowResizedCallback);
	}
	
	return window;
}

Window* GlfwWindowManager::FindGLFWWindow(GLFWwindow* window)
{
	Window* ret = nullptr;

	for (auto it : windows)
		if (static_cast<GlfwWindow*>(it.second)->window == window)
			ret = it.second;

	return ret;
}

void GlfwWindowManager::MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		double x, y;
		auto manager = GetInstance();
		auto window = manager->FindGLFWWindow(glfwWindow);
		glfwGetCursorPos(glfwWindow, &x, &y);
		if (window)
			window->NotifyMouseButtonEvent(x, y, button, action, mods);
	}
}

void GlfwWindowManager::MouseMoveCallback(GLFWwindow* glfwWindow, double x, double y)
{
	auto manager = GetInstance();
	auto window = manager->FindGLFWWindow(glfwWindow);
	if (window)
		window->NotifyMouseMoveEvent(x, y);
}

void GlfwWindowManager::MouseScrollCallback(GLFWwindow* glfwWindow, double dx, double dy)
{
	auto manager = GetInstance();
	auto window = manager->FindGLFWWindow(glfwWindow);
	if (window)
		window->NotifyMouseScrollEvent(dx, dy);
}

void GlfwWindowManager::WindowResizedCallback(GLFWwindow* glfwWindow, int width, int height)
{
	auto manager = GetInstance();
	auto window = manager->FindGLFWWindow(glfwWindow);
	if (window)
		window->NotifyWindowResizedEvent(width, height);
}

