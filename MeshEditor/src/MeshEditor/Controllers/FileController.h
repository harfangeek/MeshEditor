#pragma once

#include "Rendering/Core/MeshRenderer.h"

#include "GLM/glm.hpp"
#include <string>

namespace MeshEditor
{
	namespace Controllers
	{
		class FileController
		{
		public:
			FileController(Rendering::Core::MeshRenderer* meshRenderer);
			~FileController();
			 
			void SetPath(std::string path);
			std::string GetPath();

			std::string Load();
			std::string Save();
						
		private:
			Rendering::Core::MeshRenderer* meshRenderer;
			std::string path;
		};
	}
}
