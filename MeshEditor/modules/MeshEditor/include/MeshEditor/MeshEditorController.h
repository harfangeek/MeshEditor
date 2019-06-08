#pragma once

#include "GLM/glm.hpp"

namespace Rendering
{
	class MeshRenderer;
}

namespace MeshEditor
{
	class MeshEditorController
	{
	public:
		MeshEditorController(Rendering::MeshRenderer* meshRenderer);
		~MeshEditorController();
			 
		void SetTranslation(glm::vec3 translation);
		glm::vec3 GetTranslation();
		void SetRotation(glm::vec3 rotation);
		glm::vec3 GetRotation();
		void SetScale(glm::vec3 scale);
		glm::vec3 GetScale();
		void SetScaleKeepRatio(bool scaleKeepRatio);
		bool GetScaleKeepRatio();
			
	private:
		Rendering::MeshRenderer* meshRenderer;
		bool scaleKeepRatio;
	};
}
