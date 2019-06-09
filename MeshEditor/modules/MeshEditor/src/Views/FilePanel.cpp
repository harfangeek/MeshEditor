#include "MeshEditor/FilePanel.h"
#include "MeshEditor/FileController.h"

#include <IMGUI/imgui.h>

using namespace MeshEditor;

FilePanel::FilePanel(FileController* controller) : GUI::Panel(42)
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

