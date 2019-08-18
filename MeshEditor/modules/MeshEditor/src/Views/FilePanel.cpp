#include "MeshEditor/FilePanel.h"
#include "MeshEditor/FileController.h"

#include <IMGUI/imgui.h>
#include "PFD/portable-file-dialogs.h"

using namespace MeshEditor;

FilePanel::FilePanel(FileController* controller) : GUI::Panel(42)
{
	this->controller = controller;
}

void FilePanel::Display()
{
	ImGui::InputText("##Path", controller->GetPath(), controller->pathSize);

	ImGui::SameLine();
	if (ImGui::Button("Browse"))
	{
		auto f = pfd::open_file("Choose files to read", "./",
			{ "Obj files (.obj)", "*.obj",
			  "All Files", "*" },
			false);

		auto files = f.result();
		if (files.size() > 0)
			controller->SetPath(files[0]);
	}

	if (ImGui::Button("Load"))
		controller->Load();

	ImGui::SameLine();
	if (ImGui::Button("Save"))
		controller->Save();
}

