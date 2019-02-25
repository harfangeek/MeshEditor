#include "MeshEditor/Views/FilePanel.h"
#include <IMGUI/imgui.h>

#include <string>

using namespace MeshEditor::Views;

FilePanel::FilePanel(MeshEditor::Controllers::FileController* controller) : GUI::Interfaces::Panel(42)
{
	this->controller = controller;
	
#ifdef _MSC_VER
	strncpy_s(path, 2048, controller->GetPath().c_str(), 2047);
#else
	strncpy(path, controller->GetPath().c_str(), 2047);
#endif
}

void FilePanel::Display()
{
	ImGui::InputText("Path", path, 2048);
	if (ImGui::Button("Load"))
	{
		controller->SetPath(path);
		controller->Load();
	}
	ImGui::SameLine();
	if (ImGui::Button("Save"))
	{
		controller->SetPath(path);
		controller->Save();
	}
}

