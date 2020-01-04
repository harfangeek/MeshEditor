#pragma once

#include "GUI/Panel.h"

namespace MeshEditor
{
	class ViewerController;

	class ViewerPanel : public GUI::Panel
	{
	public:
		ViewerPanel(ViewerController* controller);
		virtual void Display();

	private:
		ViewerController* controller;
	};
}
