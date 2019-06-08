#include "MeshEditor/MeshDialog.h"
#include "Rendering/MeshRenderer.h"

using namespace MeshEditor;

MeshDialog::MeshDialog(unsigned int id, Rendering::MeshRenderer* meshRenderer) : GUI::Dialog(id, "", 0.0f, 0.0f, 0.0f, 0.0f), meshRenderer(meshRenderer)
{

}

MeshDialog::~MeshDialog()
{

}

void MeshDialog::Display()
{
	if (meshRenderer)
		meshRenderer->Display();
}

void MeshDialog::SetMeshRenderer(Rendering::MeshRenderer* meshRenderer)
{
	this->meshRenderer = meshRenderer;
}
