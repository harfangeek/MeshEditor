#pragma once

#include "Core\MeshRenderer.h"

namespace Core
{
	class WindowManager
	{
		private:
			MeshRenderer* meshRenderer;
			int width;
			int height;
			int mouseX;
			int mouseY;			

		public:
			WindowManager();
			~WindowManager();

			void Init(int widt, int height, int argc, char** argv);			
			void MouseClick(int button, int state, int x, int y);
			void MouseMotion(int x, int y);
			void MouseWheel(int button, int dir, int x, int y);
			void Reshape(int width, int height);
			void Render();
			
			void SetMeshRenderer(MeshRenderer* meshRenderer);
			MeshRenderer* GetMeshRenderer();
	};
}