#include "MeshEditor/MeshDialog.h"
#include "MeshEditor/MeshEditorPanel.h"
#include "MeshEditor/FilePanel.h"
#include "MeshEditor/ViewerPanel.h"
#include "MeshEditor/MeshEditorController.h"
#include "MeshEditor/CameraController.h"
#include "MeshEditor/FileController.h"
#include "MeshEditor/ViewerController.h"

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
	
	//unsigned char test = RenderMode::Mesh | RenderMode::FacesNormals;

	meshRenderer->SetRenderMode((RenderMode)(RenderMode::Mesh/* | RenderMode::Vertices | RenderMode::FacesNormals | RenderMode::VerticesNormals*/));
	sceneRenderer->AddMeshRenderer(meshRenderer, 42);

	MeshRenderer* meshRenderer2 = new MeshRenderer();
	meshRenderer2->SetRenderMode((RenderMode)(RenderMode::Mesh /*| RenderMode::VERTICES | RenderMode::FACES_NORMALS | RenderMode::VERTICES_NORMALS*/));
	meshRenderer2->SetTranslation(glm::vec3(0.75, 0.0, 0.0));
	sceneRenderer->AddMeshRenderer(meshRenderer2, 42);

	// Mesh dialog
	MeshDialog* meshDialog = new MeshDialog(142, sceneRenderer, &camera, 42);

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

	// Viewer dialog
	ImGuiDialog* viewerDialog = new ImGuiDialog(422, "Viewer options", 75, 75, 200, 150);
	ViewerController* viewerController = new ViewerController(meshRenderer);
	ViewerPanel* viewerPanel = new ViewerPanel(viewerController);
	viewerDialog->SetPanel(viewerPanel);

	// Add all dialogs
	window->AddDialog(meshDialog);
	window->AddDialog(meshEditorDialog);
	window->AddDialog(fileDialog);
	window->AddDialog(viewerDialog);

	// Camera controller
	CameraController* cameraController = new CameraController(&camera);
	window->AddMouseListener(cameraController);
	window->AddWindowListener(cameraController);

	// Window 2
	Window* window2 = manager->NewWindow(43, WINDOW_WIDTH, WINDOW_HEIGHT, 400, 400, "Test Window2");
	window2->SetBackgroundColor(0.75f, 0.35f, 0.40f, 1.00f);

	// Mesh editor dialog 2
	ImGuiDialog* meshEditorDialog2 = new ImGuiDialog(12, "Mesh editor2", 50, 220, 200, 400);
	MeshEditorPanel* meshEditorPanel2 = new MeshEditorPanel(meshEditorController);
	meshEditorDialog2->SetPanel(meshEditorPanel2);
	MeshDialog* meshDialog2 = new MeshDialog(143, sceneRenderer, &camera, 43);
	
	sceneRenderer->InitForContext(43);

	window2->AddDialog(meshDialog2);
	window2->AddDialog(meshEditorDialog2);
	window2->AddMouseListener(cameraController);
	window2->AddWindowListener(cameraController);

	// Start application
	manager->Start();

    return 0;
}
