#pragma once

#include "GUI/Panel.h"

namespace MeshEditor
{
	class MeshEditorController;

	class MeshEditorPanel : public GUI::Panel
	{
	public:
		MeshEditorPanel(MeshEditorController* controller);
		virtual void Display();

	private:
		MeshEditorController* controller;
	};
}
