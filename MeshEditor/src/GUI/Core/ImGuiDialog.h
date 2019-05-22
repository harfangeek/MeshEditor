#pragma once

#include "GUI/Interfaces/Dialog.h"

#include <string>

namespace GUI
{
	namespace Core
	{
		class ImGuiDialog : public GUI::Interfaces::Dialog
		{
		public:
			ImGuiDialog(unsigned int id, std::string title, float x, float y, float width, float height);
			virtual ~ImGuiDialog();

			virtual void Display();

		protected:
			
		};
	}
}