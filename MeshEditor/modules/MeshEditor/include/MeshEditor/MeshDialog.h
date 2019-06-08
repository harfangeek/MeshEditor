#pragma once

#include "GUI/Dialog.h"

namespace Rendering
{
	class MeshRenderer;
}

namespace MeshEditor
{
	// A custom Dialog not showin any GUI but just drawing in the background
	class MeshDialog : public GUI::Dialog
	{
	public:
		MeshDialog(unsigned int id, Rendering::MeshRenderer* meshRenderer=nullptr);
		virtual ~MeshDialog();
		virtual void Display();

		void SetMeshRenderer(Rendering::MeshRenderer* meshRenderer);

	private:
		Rendering::MeshRenderer* meshRenderer;
	};
}
