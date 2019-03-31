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
	auto scaleKeepRatio = controller->GetScaleKeepRatio();
	
	ImGui::Text("Translation");
	if(ImGui::DragFloat("X##1", &translation.x, 0.1f) |
		ImGui::DragFloat("Y##1", &translation.y, 0.1f) |
		ImGui::DragFloat("Z##1", &translation.z, 0.1f))
		controller->SetTranslation(translation);

	ImGui::Text("Rotation");
	if(ImGui::DragFloat("X##2", &rotation.x) |
		ImGui::DragFloat("Y##2", &rotation.y) |
		ImGui::DragFloat("Z##2", &rotation.z))
		controller->SetRotation(rotation);

	ImGui::Text("Scale");
	if (ImGui::Checkbox("Keep ratio", &scaleKeepRatio))
	{
		controller->SetScaleKeepRatio(scaleKeepRatio);
	}

	if (scaleKeepRatio)
	{
		if (ImGui::DragFloat("Ratio", &scale.x, 0.1f))
		{
			controller->SetScale(scale);
		}
	}
	else if (ImGui::DragFloat("X##3", &scale.x, 0.1f) |
		ImGui::DragFloat("Y##3", &scale.y, 0.1f) |
		ImGui::DragFloat("Z##3", &scale.z, 0.1f))
	{
		controller->SetScale(scale);
	}
}

