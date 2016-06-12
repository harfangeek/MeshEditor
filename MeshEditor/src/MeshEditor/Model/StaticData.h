#pragma once

#include "GUI\Interfaces\Window.h"
#include "Rendering\Core\MeshRenderer.h"

namespace MeshEditor
{
	namespace Model
	{
		class StaticData
		{
		public:
			static void SetWindowManager(GUI::Interfaces::Window* windowManager);
			static GUI::Interfaces::Window* GetWindowManager();
			static void SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer);
			static Rendering::Core::MeshRenderer* GetMeshRenderer();
		};
	}
}