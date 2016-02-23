#pragma once

#include "Core\MeshRenderer.h"

#define NB_MOUSE_BUTTON 3

namespace Core
{
	enum MouseButton { RIGHT=0, MIDDLE=1, LEFT=2};
	class WindowManager
	{
		private:
			MeshRenderer* meshRenderer;
			int width;
			int height;
			int mouseX;
			int mouseY;
			bool mouseButtons[NB_MOUSE_BUTTON];

		public:
			WindowManager();
			~WindowManager();

			void Init(int widt, int height, int argc, char** argv);			
			void MouseClick(MouseButton button, bool state, int x, int y);
			void MouseMotion(int x, int y);
			void MouseWheel(int wheel, int dir, int x, int y);
			void Reshape(int width, int height);
			void Render();
			
			void SetMeshRenderer(MeshRenderer* meshRenderer);
			MeshRenderer* GetMeshRenderer();
	};
}