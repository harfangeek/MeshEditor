#pragma once

#include "GUI\Core\WindowManager.h"
#include "Rendering\Core\MeshRenderer.h"

namespace MeshEditor
{
	namespace Model
	{
		class StaticData
		{
		public:
			static void SetWindowManager(GUI::Core::WindowManager* windowManager);
			static GUI::Core::WindowManager* GetWindowManager();
			static void SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer);
			static Rendering::Core::MeshRenderer* GetMeshRenderer();
		};
	}
}