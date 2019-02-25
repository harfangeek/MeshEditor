#pragma once

#include "GUI/Interfaces/Panel.h"
#include "MeshEditor/Controllers/FileController.h"

namespace MeshEditor
{
	namespace Views
	{
		class FilePanel : public GUI::Interfaces::Panel
		{
		public:
			FilePanel(MeshEditor::Controllers::FileController* controller);
			virtual void Display();

		private:
			MeshEditor::Controllers::FileController* controller;
			char path[2048];
		};
	}
}