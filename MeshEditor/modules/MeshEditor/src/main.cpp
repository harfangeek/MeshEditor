#include "MeshEditor/MeshDialog.h"
#include "MeshEditor/MeshEditorPanel.h"
#include "MeshEditor/FilePanel.h"
#include "MeshEditor/MeshEditorController.h"
#include "MeshEditor/CameraController.h"
#include "MeshEditor/FileController.h"

#include "GUI/Window.h"
#include "GUI/WindowManager.h"
#include "GUI/ImGuiDialog.h"
#include "GUI/GlfwWindowManager.h"

#include "Rendering/SceneRenderer.h"
#include "Rendering/MeshRenderer.h"
#include "Rendering/Light.h"
#include "Rendering/Camera.h"

using namespace MeshEditor;
using namespace Rendering;
using namespace GUI;

constexpr unsigned int WINDOW_WIDTH = 1200;
constexpr unsigned int WINDOW_HEIGHT = 700;

int main(int, char**)
{
	// Create window manager
	WindowManager* manager = GlfwWindowManager::GetInstance();
	
	Window* window = manager->NewWindow(42, WINDOW_WIDTH, WINDOW_HEIGHT, 400, 400, "Test Window");
	window->SetBackgroundColor(0.45f, 0.55f, 0.60f, 1.00f);

	// Create the scene
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	Light light;
	light.SetType(LightType::POINT_LIGHT);
	light.SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SceneRenderer* sceneRenderer = new SceneRenderer(&camera, &light);
	
	// Create Mesh renderer
	MeshRenderer* meshRenderer = new MeshRenderer();	
	meshRenderer->SetRenderMode((RenderMode)(RenderMode::MESH /*| RenderMode::VERTICES | RenderMode::FACES_NORMALS | RenderMode::VERTICES_NORMALS*/));
	sceneRenderer->AddMeshRenderer(meshRenderer);

	// Mesh dialog
	MeshDialog* meshDialog = new MeshDialog(142, sceneRenderer, &camera);

	// Mesh editor dialog
	ImGuiDialog* meshEditorDialog = new ImGuiDialog(12, "Mesh editor", 50, 220, 200, 400);
	MeshEditorController* meshEditorController = new MeshEditorController(meshRenderer);
	MeshEditorPanel* meshEditorPanel = new MeshEditorPanel(meshEditorController);
	meshEditorDialog->SetPanel(meshEditorPanel);

	// File dialog
	ImGuiDialog* fileDialog = new ImGuiDialog(1, "File dialog", 50, 50, 200, 150);
	FileController* fileController = new FileController(meshRenderer);
	FilePanel* filePanel = new FilePanel(fileController);
	fileDialog->SetPanel(filePanel);

	// Add all dialogs
	window->AddDialog(meshDialog);
	window->AddDialog(meshEditorDialog);
	window->AddDialog(fileDialog);

	// Camera controller
	CameraController* cameraController = new CameraController(&camera);
	window->AddMouseListener(cameraController);
	window->AddWindowListener(cameraController);

	// Start application
	manager->Start();

    return 0;
}
