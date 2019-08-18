#pragma once

#include <string>

namespace Rendering
{
	class MeshRenderer;
}

namespace MeshEditor
{
	class FileController
	{
	public:
		FileController(Rendering::MeshRenderer* meshRenderer);
		~FileController();
			 
		void SetPath(std::string newPath);
		char* GetPath();
		static const int pathSize = 2048;

		std::string Load();
		std::string Save();
						
	private:
		Rendering::MeshRenderer* meshRenderer;
		
		char path[pathSize];
	};
}
