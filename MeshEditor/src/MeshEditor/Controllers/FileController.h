#pragma once

#include <string>

namespace Rendering
{
	namespace Core
	{
		class MeshRenderer;
	}
}

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
