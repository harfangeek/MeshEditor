#include "GUI/GlfwWindow.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

using namespace GUI;
using namespace std;

GlfwWindow::GlfwWindow(unsigned int id, unsigned int width, unsigned int height, int x, int y, string title, GlfwWindow* sharedWindow) : Window(id, width, height, x, y, title), glfwContext(nullptr)
{
	imguiContext = nullptr;
	GLFWwindow *sharedContext = nullptr;
	sharedGLContext = false;
	ImFontAtlas* fontAtlas = nullptr;
	if (sharedWindow)
	{
		sharedContext = sharedWindow->window;
		sharedGLContext = true;
		if (sharedWindow->imguiContext)
		{
			sharedGLContext = true;
			ImGui::SetCurrentContext(sharedWindow->imguiContext);
			auto io = ImGui::GetIO();
			fontAtlas = io.Fonts;
		}
	}

	// Create window with graphics context
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, sharedContext);
	imguiContext = ImGui::CreateContext(fontAtlas);
	ImGui::SetCurrentContext(imguiContext);
	ImGui::StyleColorsDark();
}

void GlfwWindow::Init()
{
	if (window == nullptr)
		return;
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!sharedGLContext)
	{
		bool err = gl3wInit() != 0;
		if (err)
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");

		const char* glsl_version = "#version 330";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
		
	glfwContext = ImGui_ImplGlfw_InitForOpenGL(window, true);
}

GlfwWindow::~GlfwWindow()
{

}

void GlfwWindow::SetWindow()
{
	glfwMakeContextCurrent(window);
}

void GlfwWindow::Resize(unsigned int width, unsigned int height)
{
	Window::Resize(width, height);
}

void GlfwWindow::Move(int x, int y)
{
	Window::Move(x, y);
}

void GlfwWindow::SetTitle(std::string title)
{
	Window::SetTitle(title);
}

void GlfwWindow::PreDisplay()
{
	ImGui::SetCurrentContext(imguiContext);
	ImGui_ImplGlfw_SetContext(glfwContext);
	glfwMakeContextCurrent(window);
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

inline void GlfwWindow::Display()
{
	PreDisplay();
	Window::Display();
	PostDisplay();
}

inline void GlfwWindow::PostDisplay()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
}

