#include "GUI/GlfwWindowManager.h"
#include "GUI/GlfwWindow.h"

#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

using namespace GUI;
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

	initialized = true;
}

void GlfwWindowManager::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();

	for (auto pair : windows)
	{
		if (pair.second != NULL)
		{
			GlfwWindow* window = dynamic_cast<GlfwWindow*>(pair.second);
			if (window)
			{
				ImGui_ImplGlfw_Shutdown(window->glfwContext);
				ImGui::DestroyContext(window->imguiContext);
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

Window* GlfwWindowManager::NewWindow(unsigned int id, unsigned int width, unsigned int height, int posX, int posY, string title, Window* sharedWindow)
{
	// Create window with graphics context
	GlfwWindow* window = new GlfwWindow(id, width, height, posX, posY, title, dynamic_cast<GlfwWindow*>(sharedWindow));

	if (window && window->window)
	{
		windows[id] = window;

		glfwSetMouseButtonCallback(window->window, GlfwWindowManager::MouseButtonCallback);
		glfwSetCursorPosCallback(window->window, GlfwWindowManager::MouseMoveCallback);
		glfwSetScrollCallback(window->window, GlfwWindowManager::MouseScrollCallback);
		glfwSetWindowSizeCallback(window->window, GlfwWindowManager::WindowResizedCallback);
	}

	window->Init();
	
	return window;
}

GlfwWindow* GlfwWindowManager::FindGLFWWindow(GLFWwindow* window)
{
	Window* ret = nullptr;

	for (auto it : windows)
		if (static_cast<GlfwWindow*>(it.second)->window == window)
			ret = it.second;

	return dynamic_cast<GlfwWindow*>(ret);
}

void GlfwWindowManager::MouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
	auto manager = GetInstance();
	auto window = manager->FindGLFWWindow(glfwWindow);
	auto prevContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(window->imguiContext);

	if (!ImGui::GetIO().WantCaptureMouse)
	{
		double x, y;
		auto manager = GetInstance();
		auto window = manager->FindGLFWWindow(glfwWindow);
		glfwGetCursorPos(glfwWindow, &x, &y);
		if (window)
			window->NotifyMouseButtonEvent(x, y, button, action, mods);
	}

	ImGui::SetCurrentContext(prevContext);
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

