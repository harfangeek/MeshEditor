#include "MeshEditor/Views/MeshDialog.h"

using namespace MeshEditor::Views;

MeshDialog::MeshDialog(unsigned int id, Rendering::Core::MeshRenderer* meshRenderer) : Dialog(id, "", 0.0f, 0.0f, 0.0f, 0.0f), meshRenderer(meshRenderer)
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

void MeshDialog::SetMeshRenderer(Rendering::Core::MeshRenderer* meshRenderer)
{
	this->meshRenderer = meshRenderer;
}
