#include "GUI/Core/ImGuiDialog.h"

#include <IMGUI/imgui.h>

using namespace GUI::Core;

ImGuiDialog::ImGuiDialog(unsigned int id, std::string title, float x, float y, float width, float height) : Dialog(id, title, x, y, width, height)
{
}

ImGuiDialog::~ImGuiDialog()
{
}

void ImGuiDialog::Display()
{
	ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
	ImGui::Begin(title.c_str());

	if(panel)
		panel->Display();

	ImGui::End();
}
