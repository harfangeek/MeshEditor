#pragma once

#include "GUI\Interfaces\EventListener.h"
#include "Rendering\Core\MeshRenderer.h"

namespace MeshEditor
{
	namespace Operators
	{
		class MouseManipulator : public GUI::Interfaces::EventListener
		{
		public:
			MouseManipulator(Rendering::Core::MeshRenderer* meshRenderer);
			~MouseManipulator();

			virtual void OnEvent(const GUI::Model::Event* event);

		private:
			Rendering::Core::MeshRenderer* meshRenderer;
		};
	}
}