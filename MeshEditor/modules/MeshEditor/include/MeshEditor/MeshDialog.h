#pragma once

#include "GUI/Dialog.h"

namespace Rendering
{
	class SceneRenderer;
	class Camera;
}

namespace MeshEditor
{
	// A custom Dialog not showin any GUI but just drawing in the background
	class MeshDialog : public GUI::Dialog
	{
	public:
		MeshDialog(unsigned int id, Rendering::SceneRenderer* sceneRenderer=nullptr, Rendering::Camera* camera=nullptr, unsigned int context = 0);
		virtual ~MeshDialog();
		virtual void Display();

		void SetSceneRenderer(Rendering::SceneRenderer* sceneRenderer);
		void SetCamera(Rendering::Camera* camera);

	private:
		Rendering::SceneRenderer* sceneRenderer;
		Rendering::Camera* camera;
		unsigned int context;
	};
}
