#pragma once

#include "GUI\Interfaces\EventListener.h"
#include "Rendering\Core\MeshRenderer.h"

namespace MeshEditor
{
	namespace Operators
	{
		class MouseSelector : public GUI::Interfaces::EventListener
		{
		public:
			MouseSelector(Rendering::Core::MeshRenderer* meshRenderer);
			~MouseSelector();

			virtual void OnEvent(const GUI::Model::Event* event);

		private:
			Rendering::Core::MeshRenderer* meshRenderer;
		};
	}
}