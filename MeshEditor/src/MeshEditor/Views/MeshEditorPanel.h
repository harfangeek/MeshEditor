#pragma once

#include "GUI/Interfaces/Panel.h"
#include "MeshEditor/Controllers/MeshEditorController.h"

namespace MeshEditor
{
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