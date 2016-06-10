#include <iostream>
#include <vector>
#include "Dependencies\glew\include\glew.h"
#include "Rendering\Model\Mesh.h"
#include "MeshEditor\Model\StaticData.h"
#include "Rendering\Operators\ObjReader.h"
#include "Rendering\Operators\MeshConverter.h"
#include "Rendering\Operators\MeshTransformation.h"
#include "Rendering\Core\ShaderLoader.h"
#include "Rendering\Core\MeshRenderer.h"
#include "GUI\Core\WindowManager.h"
#include "GUI\Core\FreeglutWrapper.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

using namespace MeshEditor::Model;
using namespace GUI::Core;
using namespace Rendering::Core;
using namespace Rendering::Model;

int main(int argc, char** argv)
{
	// Create freeglut window
	WindowManager* windowManager = new GUI::Core::WindowManager();
	StaticData::SetWindowManager(windowManager);
	windowManager->Init(WINDOW_WIDTH, WINDOW_HEIGHT, argc, argv);

	// Create mesh renderer (init openGL)
	MeshRenderer* meshRenderer = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	StaticData::SetMeshRenderer(meshRenderer);
	windowManager->SetMeshRenderer(meshRenderer);
	meshRenderer->Init();

	// Load mesh
	Mesh* mesh = NULL;
	Rendering::Operators::ObjReader::LoadMesh("Models\\apple.obj", mesh, true);

	Rendering::Operators::MeshTransformation::Triangulate(mesh);
	mesh->ComputeNormals();
	mesh->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	meshRenderer->SetMesh(mesh);

	meshRenderer->SetRenderMode((RenderMode)(RenderMode::MESH /*| Core::RenderMode::VERTICES | Core::RenderMode::WIREFRAME/* | Core::RenderMode::FACES_NORMALS | Core::RenderMode::VERTICES_NORMALS*/));
	meshRenderer->SetLightType(LightType::POINT_LIGHT);
	meshRenderer->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//Operators::MeshTransformation::Inflate(mesh, 0.1f);
	//meshRenderer->UpdateMeshConnectivity();

	// Start main loop
	StartGlut();

	delete windowManager;
	delete meshRenderer;

	return 0;
}
