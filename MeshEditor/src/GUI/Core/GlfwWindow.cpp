#include "GUI/Core/GlfwWindow.h"

#include <GL/gl3w.h>

#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>


using namespace GUI::Core;
using namespace std;

GlfwWindow::GlfwWindow(unsigned int id, unsigned int width, unsigned int height, int x, int y, string title, GlfwWindow* share) : Window(id, width, height, x, y, title)
{
	GLFWwindow *sharedWindow = NULL;
	if (share)
		sharedWindow = share->window;

	// Create window with graphics context
	window = glfwCreateWindow(width, height, title.c_str(), NULL, sharedWindow);
	if (window == NULL)
		return ;

	/*ImGuiContext* ctx = ImGui::GetCurrentContext();
	ImGui::GetFont();
	ImFontAtlas* ImGui::font
	if(ctx != NULLL)*/

	//imguiContext = ImGui::CreateContext();
	//ImGui::SetCurrentContext(imguiContext);
	//ImGui::StyleColorsDark();
	
	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	bool err = gl3wInit() != 0;
	if (err)
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
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
	glfwMakeContextCurrent(window);
	glfwPollEvents();
	//glfwWaitEvents();

	//ImGui::SetCurrentContext(imguiContext);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
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

