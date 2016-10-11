#pragma once

#include "Rendering\Core\MeshRenderer.h"
#include "GUI\Interfaces\EventListener.h"

namespace MeshEditor
{
	namespace Core
	{
		class WindowRenderer : public GUI::Interfaces::EventListener
		{
		public:
			WindowRenderer(Rendering::Core::MeshRenderer* meshRenderer);
			virtual void OnEvent(const GUI::Model::Event* event);

		private:
			Rendering::Core::MeshRenderer* meshRenderer;
		};
	}
}