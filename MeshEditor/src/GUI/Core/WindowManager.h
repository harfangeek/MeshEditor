#pragma once

#include "GUI\Interfaces\IWindowManager.h"
#include "Rendering\Core\MeshRenderer.h"

namespace GUI
{
	namespace Core
	{
		class WindowManager
		{
		private:
			Rendering::Core::MeshRenderer* meshRenderer;
			int width;
			int height;			

		public:
			WindowManager();
			~WindowManager();

			void Init(int widt, int height, int argc, char** argv);
			void Reshape(int width, int height);
			void Render();

			void SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer);
			Rendering::Core::MeshRenderer* GetMeshRenderer();
		};
	}
}