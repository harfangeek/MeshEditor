#include "MeshEditor/ViewerPanel.h"
#include "MeshEditor/ViewerController.h"

#include <IMGUI/imgui.h>

using namespace MeshEditor;

ViewerPanel::ViewerPanel(ViewerController* controller) : GUI::Panel(422)
{
	this->controller = controller;
}

void ViewerPanel::Display()
{
	constexpr int colorFlags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop;

	if (ImGui::Checkbox("Mesh", &controller->mesh)) controller->Update();
	ImGui::SameLine(); if (ImGui::ColorEdit4("##MeshColor", controller->meshColor, colorFlags)) controller->Update();
	if (ImGui::Checkbox("Wireframe", &controller->wireframe)) controller->Update();
	ImGui::SameLine(); if (ImGui::ColorEdit4("##WireframeColor", controller->wireframeColor, colorFlags)) controller->Update();
	if (ImGui::Checkbox("Vertices", &controller->vertices)) controller->Update();
	ImGui::SameLine(); if (ImGui::ColorEdit4("##VerticesColor", controller->verticesColor, colorFlags)) controller->Update();
	if (ImGui::Checkbox("Faces normals", &controller->facesNormals)) controller->Update();
	ImGui::SameLine(); if (ImGui::ColorEdit4("##FacesNormalsColor", controller->facesNormalsColor, colorFlags)) controller->Update();
	if (ImGui::Checkbox("Vertices normals", &controller->verticesNormals)) controller->Update();
	ImGui::SameLine(); if (ImGui::ColorEdit4("##VerticesNormalsColor", controller->verticesNormalsColor, colorFlags)) controller->Update();
}
