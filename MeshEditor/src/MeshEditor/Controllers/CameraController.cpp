#include "MeshEditor/Controllers/CameraController.h"
#include "GUI/Interfaces/Window.h"
#include "Rendering/Core/MeshRenderer.h"

#include <GLFW/glfw3.h>

using namespace Rendering::Core;
using namespace MeshEditor::Controllers;
using namespace GUI::Interfaces;

CameraController::CameraController(Rendering::Core::MeshRenderer* meshRenderer) : translate(false), rotate(false), meshRenderer(meshRenderer)
{

}

CameraController::~CameraController()
{

}

void CameraController::OnMouseButtonEvent(GUI::Interfaces::Window* window, double x, double y, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
		rotate = action == GLFW_PRESS;
	else if(button == GLFW_MOUSE_BUTTON_2)
		translate = action == GLFW_PRESS;
}

void CameraController::OnMouseMoveEvent(GUI::Interfaces::Window* window, double x, double y, double dx, double dy)
{
	float rdx = static_cast<float>(dx) / static_cast<float>(window->GetWidth());
	float rdy = static_cast<float>(dy) / static_cast<float>(window->GetHeight());

	if (rotate)
		meshRenderer->Rotate(rdx, rdy);
	else if (translate)
		meshRenderer->Translate(-rdx * 5.0f, rdy * 5.0f);
}

void CameraController::OnMouseScrollEvent(GUI::Interfaces::Window* window, double dx, double dy)
{
	meshRenderer->Zoom(static_cast<float>(dy) * 0.1f);
}

void CameraController::OnWindowResizedEvent(GUI::Interfaces::Window* window, int width, int height)
{
	meshRenderer->SetViewPort(width, height);
}
