#pragma once

#include "Core\WindowManager.h"
#include "Core\MeshRenderer.h"

namespace Model
{
	class StaticData
	{
		public:
			static void SetWindowManager(Core::WindowManager* windowManager);
			static Core::WindowManager* GetWindowManager();
			static void SetMeshRenderer(Core::MeshRenderer* meshRenderer);
			static Core::MeshRenderer* GetMeshRenderer();
	};
}