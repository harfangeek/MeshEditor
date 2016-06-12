#pragma once

#include "GUI\Interfaces\Window.h"
#include "GUI\Core\GlutWindowManager.h"
#include <map>
#include <string>

namespace GUI
{
	namespace Core
	{
		class GlutWindow : public GUI::Interfaces::Window
		{
		private:
			friend class GlutWindowManager;
			GlutWindow(int width, int height, int posX, int posY, std::string title);

			// Instance data
			int id;
			int width;
			int height;
			int x;
			int y;
			std::string title;
			//Rendering::Core::MeshRenderer* meshRenderer;

			void CreateGlutWindow();

		public:
			
			virtual ~GlutWindow();


			/*void Reshape(int width, int height);
			void Render();

			void SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer);
			Rendering::Core::MeshRenderer* GetMeshRenderer();*/
		};
	}
}