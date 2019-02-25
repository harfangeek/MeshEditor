#pragma once

#include "GUI/Interfaces/Dialog.h"
#include "Rendering/Core/MeshRenderer.h"

namespace MeshEditor
{
	namespace Views
	{
		// A custom Dialog not showin any GUI but just drawing in the background
		class MeshDialog : public GUI::Interfaces::Dialog
		{
		public:
			MeshDialog(unsigned int id, Rendering::Core::MeshRenderer* meshRenderer=nullptr);
			virtual ~MeshDialog();
			virtual void Display();

			void SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer);

		private:
			Rendering::Core::MeshRenderer* meshRenderer;
		};
	}
}
