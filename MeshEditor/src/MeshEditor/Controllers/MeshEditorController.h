#pragma once

#include "Rendering/Core/MeshRenderer.h"

#include "GLM/glm.hpp"

namespace MeshEditor
{
	namespace Controllers
	{
		class MeshEditorController
		{
		public:
			MeshEditorController(Rendering::Core::MeshRenderer* meshRenderer);
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
			Rendering::Core::MeshRenderer* meshRenderer;
			bool scaleKeepRatio;
		};
	}
}
