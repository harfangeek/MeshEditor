#include "Model\StaticData.h"

using namespace Model;

Core::WindowManager* staticWindowManager;
Core::MeshRenderer* staticMeshRenderer;

void StaticData::SetWindowManager(Core::WindowManager* windowManager)
{
	staticWindowManager = windowManager;
}

Core::WindowManager* StaticData::GetWindowManager()
{
	return staticWindowManager;
}

void StaticData::SetMeshRenderer(Core::MeshRenderer* meshRenderer)
{
	staticMeshRenderer = meshRenderer;
}

Core::MeshRenderer* StaticData::GetMeshRenderer()
{
	return staticMeshRenderer;
}
