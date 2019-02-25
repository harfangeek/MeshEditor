#include "MeshEditor/Views/MeshEditorPanel.h"
#include <IMGUI/imgui.h>

using namespace MeshEditor::Views;

MeshEditorPanel::MeshEditorPanel(MeshEditor::Controllers::MeshEditorController* controller) : GUI::Interfaces::Panel(42)
{
	this->controller = controller;
}

void MeshEditorPanel::Display()
{
	auto translation = controller->GetTranslation();
	auto rotation = controller->GetRotation();
	auto scale = controller->GetScale();
	
	ImGui::Text("Translation");
	if(ImGui::DragFloat("X##1", &translation.x) |
		ImGui::DragFloat("Y##1", &translation.y) |
		ImGui::DragFloat("Z##1", &translation.z))
		controller->SetTranslation(translation);

	ImGui::Text("Rotation");
	if(ImGui::DragFloat("X##2", &rotation.x) |
		ImGui::DragFloat("Y##2", &rotation.y) |
		ImGui::DragFloat("Z##2", &rotation.z))
		controller->SetRotation(rotation);

	ImGui::Text("Scale");
	if(ImGui::DragFloat("X##3", &scale.x) |
		ImGui::DragFloat("Y##3", &scale.y) |
		ImGui::DragFloat("Z##3", &scale.z))
		controller->SetScale(scale);
}

