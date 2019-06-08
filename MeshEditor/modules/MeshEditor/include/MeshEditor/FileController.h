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
			 
		void SetPath(std::string path);
		std::string GetPath();

		std::string Load();
		std::string Save();
						
	private:
		Rendering::MeshRenderer* meshRenderer;
		std::string path;
	};
}
