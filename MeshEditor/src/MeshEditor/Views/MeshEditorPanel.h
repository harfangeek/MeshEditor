#pragma once

#include "GUI/Interfaces/Panel.h"

namespace MeshEditor
{
	namespace Controllers
	{
		class MeshEditorController;
	}

	namespace Views
	{
		class MeshEditorPanel : public GUI::Interfaces::Panel
		{
		public:
			MeshEditorPanel(MeshEditor::Controllers::MeshEditorController* controller);
			virtual void Display();

		private:
			MeshEditor::Controllers::MeshEditorController* controller;
		};
	}
}
