#include "MeshEditor/MeshDialog.h"
#include "Rendering/SceneRenderer.h"
#include "Rendering/Camera.h"

using namespace MeshEditor;

MeshDialog::MeshDialog(unsigned int id, Rendering::SceneRenderer* sceneRenderer, Rendering::Camera* camera) : GUI::Dialog(id, "", 0.0f, 0.0f, 0.0f, 0.0f),
																											sceneRenderer(sceneRenderer),
																											camera(camera)
{

}

MeshDialog::~MeshDialog()
{

}

void MeshDialog::Display()
{
	if (sceneRenderer && camera)
		sceneRenderer->Display(camera);
}

void MeshDialog::SetSceneRenderer(Rendering::SceneRenderer* sceneRenderer)
{
	this->sceneRenderer = sceneRenderer;
}

void MeshDialog::SetCamera(Rendering::Camera* camera)
{
	this->camera = camera;
}