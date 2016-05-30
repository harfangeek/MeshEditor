#include "MeshEditor\Model\StaticData.h"

using namespace MeshEditor::Model;
using namespace GUI::Core;
using namespace Rendering::Core;

WindowManager* staticWindowManager;
MeshRenderer* staticMeshRenderer;

void StaticData::SetWindowManager(WindowManager* windowManager)
{
	staticWindowManager = windowManager;
}

WindowManager* StaticData::GetWindowManager()
{
	return staticWindowManager;
}

void StaticData::SetMeshRenderer(MeshRenderer* meshRenderer)
{
	staticMeshRenderer = meshRenderer;
}

MeshRenderer* StaticData::GetMeshRenderer()
{
	return staticMeshRenderer;
}
