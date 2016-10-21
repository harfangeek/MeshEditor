#include <iostream>
#include <vector>
#include "Dependencies\glew\include\glew.h"

#include "Rendering\Model\Mesh.h"
#include "Rendering\Operators\ObjReader.h"
#include "Rendering\Operators\MeshConverter.h"
#include "Rendering\Operators\MeshTransformation.h"
#include "Rendering\Core\MeshRenderer.h"

#include "GUI\Interfaces\Window.h"
#include "GUI\Core\GlutWindow.h"
#include "GUI\Interfaces\Mouse.h"

//#include "MeshEditor\Model\StaticData.h"
#include "MeshEditor\Core\WindowRenderer.h"
#include "MeshEditor\Operators\MouseManipulator.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

using namespace GUI::Core;
using namespace GUI::Interfaces;
using namespace Rendering::Core;
using namespace Rendering::Model;
using namespace MeshEditor::Core;
using namespace MeshEditor::Operators;

int main(int argc, char** argv)
{
	// Create freeglut window
	GlutWindowManager* windowMgr = GlutWindowManager::GetInstance();
	//StaticData::SetWindowManager(windowManager);
	windowMgr->Init(argc, argv);
	Window* window = windowMgr->NewWindow(1, 500, 500, 200, 200, "Window 1");

	// Create mesh renderer (init openGL)
	MeshRenderer* meshRenderer = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	//StaticData::SetMeshRenderer(meshRenderer);
	meshRenderer->Init();

	// Load mesh
	Mesh* mesh = NULL;
	Rendering::Operators::ObjReader::LoadMesh("Models\\cube.obj", mesh, true);

	Rendering::Operators::MeshTransformation::Triangulate(mesh);
	mesh->ComputeNormals();
	mesh->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	meshRenderer->SetMesh(mesh);

	meshRenderer->SetRenderMode((RenderMode)(RenderMode::VERTICES | RenderMode::WIREFRAME));
	meshRenderer->SetLightType(LightType::POINT_LIGHT);
	meshRenderer->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//Operators::MeshTransformation::Inflate(mesh, 0.1f);
	//meshRenderer->UpdateMeshConnectivity();

	// Create a WindowRenderer and link it to the window
	WindowRenderer winRenderer(meshRenderer);
	window->Attach(&winRenderer);

	// Create manipulators
	MouseManipulator mouseManip(meshRenderer);
	Mouse* mouse = windowMgr->GetMouse();
	mouse->Attach(&mouseManip);

	// Start main loop
	windowMgr->Display();

	//delete windowManager;
	delete meshRenderer;

	return 0;	
}
