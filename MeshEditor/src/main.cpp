#include <iostream>
#include <vector>
#include "Dependencies\glew\glew.h"
#include "Model\Mesh.h"
#include "Model\StaticData.h"
#include "Operators\ObjReader.h"
#include "Operators\MeshConverter.h"
#include "Core\ShaderLoader.h"
#include "Core\MeshRenderer.h"
#include "Core\WindowManager.h"
#include "Core\FreeglutWrapper.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int main(int argc, char** argv)
{
	// Create freeglut window
	Core::WindowManager* windowManager = new Core::WindowManager();
	Model::StaticData::SetWindowManager(windowManager);
	windowManager->Init(600, 600, argc, argv);

	// Create mesh renderer (init openGL)
	Core::MeshRenderer* meshRenderer = new Core::MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	Model::StaticData::SetMeshRenderer(meshRenderer);
	windowManager->SetMeshRenderer(meshRenderer);
	meshRenderer->Init();

	// Load mesh
	Model::Mesh* mesh = NULL;
	Operators::ObjReader::LoadMesh(mesh, true);		
	meshRenderer->SetMesh(mesh);

	// Start main loop
	StartGlut();

	delete windowManager;
	delete meshRenderer;

	return 0;
}
