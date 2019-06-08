#pragma once

#include "GUI/Panel.h"

namespace MeshEditor
{
	class FileController;

	class FilePanel : public GUI::Panel
	{
	public:
		FilePanel(FileController* controller);
		virtual void Display();

	private:
		FileController* controller;
		char path[2048];
	};
}