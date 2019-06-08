#pragma once

#include "GUI/Dialog.h"

#include <string>

namespace GUI
{
	class ImGuiDialog : public GUI::Dialog
	{
	public:
		ImGuiDialog(unsigned int id, std::string title, float x, float y, float width, float height);
		virtual ~ImGuiDialog();

		virtual void Display();

	protected:
			
	};
}
