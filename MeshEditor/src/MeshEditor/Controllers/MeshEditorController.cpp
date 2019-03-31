#include "MeshEditor/Controllers/MeshEditorController.h"
#include "Rendering/Operators/ViewerUtility.h"
#include <vector>

using namespace Rendering::Core;
using namespace Rendering::Operators;
using namespace MeshEditor::Controllers;
using namespace GUI::Interfaces;
using namespace std;

MeshEditorController::MeshEditorController(Rendering::Core::MeshRenderer* meshRenderer) : meshRenderer(meshRenderer), scaleKeepRatio(true)
{

}

MeshEditorController::~MeshEditorController()
{

}

void MeshEditorController::SetTranslation(glm::vec3 translation)
{
	if (meshRenderer)
		meshRenderer->SetTranslation(translation);
}

glm::vec3 MeshEditorController::GetTranslation()
{
	if (meshRenderer)
		return meshRenderer->GetTranslation();

	return glm::vec3(0.0f, 0.0f, 0.0f);
}

void MeshEditorController::SetRotation(glm::vec3 rotation)
{
	if (meshRenderer)
		meshRenderer->SetRotation(rotation);
}

glm::vec3 MeshEditorController::GetRotation()
{
	if (meshRenderer)
		return meshRenderer->GetRotation();

	return glm::vec3(0.0f, 0.0f, 0.0f);
}

void MeshEditorController::SetScale(glm::vec3 scale)
{
	if (scaleKeepRatio)
		scale.y = scale.z = scale.x;

	if (meshRenderer)
		meshRenderer->SetScale(scale);
}

glm::vec3 MeshEditorController::GetScale()
{
	if (meshRenderer)
		return meshRenderer->GetScale();

	return glm::vec3(1.0f, 1.0f, 1.0f);
}

void MeshEditorController::SetScaleKeepRatio(bool scaleKeepRatio)
{
	this->scaleKeepRatio = scaleKeepRatio;

	if (scaleKeepRatio)
		SetScale(GetScale());
}

bool MeshEditorController::GetScaleKeepRatio()
{
	return this->scaleKeepRatio;
}
