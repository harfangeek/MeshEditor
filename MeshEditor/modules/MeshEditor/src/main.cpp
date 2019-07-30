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

#include "Rendering/MeshRenderer.h"

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
	
	// Create Mesh renderer
	MeshRenderer* meshRenderer = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	meshRenderer->Init();
	meshRenderer->SetLightType(LightType::POINT_LIGHT);
	meshRenderer->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshRenderer->SetRenderMode((RenderMode)(RenderMode::MESH | RenderMode::WIREFRAME | RenderMode::VERTICES | RenderMode::FACES_NORMALS | RenderMode::VERTICES_NORMALS));

	// Mesh dialog
	MeshDialog* meshDialog = new MeshDialog(142);
	meshDialog->SetMeshRenderer(meshRenderer);

	//MeshDialog* meshDialog2 = new MeshDialog(1422);
	//meshDialog2->SetMeshRenderer(meshRenderer);

	// Mesh editor dialog
	ImGuiDialog* meshEditorDialog = new ImGuiDialog(12, "Mesh editor1", 50, 220, 200, 400);
	MeshEditorController* meshEditorController = new MeshEditorController(meshRenderer);
	MeshEditorPanel* meshEditorPanel = new MeshEditorPanel(meshEditorController);
	meshEditorDialog->SetPanel(meshEditorPanel);

	/*ImGuiDialog* meshEditorDialog2 = new ImGuiDialog(122, "Mesh editor2##2", 50, 220, 200, 400);
	MeshEditorController* meshEditorController2 = new MeshEditorController(meshRenderer);
	MeshEditorPanel* meshEditorPanel2 = new MeshEditorPanel(meshEditorController2);
	meshEditorDialog2->SetPanel(meshEditorPanel2);*/

	/*ImGuiDialog* meshEditorDialog3 = new ImGuiDialog(1222, "Mesh editor3##3", 50, 220, 200, 400);
	MeshEditorController* meshEditorController3 = new MeshEditorController(meshRenderer);
	MeshEditorPanel* meshEditorPanel3 = new MeshEditorPanel(meshEditorController3);
	meshEditorDialog3->SetPanel(meshEditorPanel3);*/

	// File dialog
	//ImGuiDialog* fileDialog = new ImGuiDialog(1, "File dialog", 50, 50, 200, 150);
	FileController* fileController = new FileController(meshRenderer);
	//FilePanel* filePanel = new FilePanel(fileController);
	//fileDialog->SetPanel(filePanel);

	// Add all dialogs
	window->AddDialog(meshDialog);
	window->AddDialog(meshEditorDialog);
	/*window->AddDialog(fileDialog);

	window->AddDialog(meshEditorDialog2);*/

	//window2->AddDialog(meshDialog2);
	//window2->AddDialog(meshEditorDialog3);
	
	// Camera controller
	CameraController* cameraController = new CameraController(meshRenderer);
	window->AddMouseListener(cameraController);
	window->AddWindowListener(cameraController);

	//CameraController* cameraController2 = new CameraController(meshRenderer);
	//window2->AddMouseListener(cameraController2);
	//window2->AddWindowListener(cameraController2);

	// Load mesh
	fileController->SetPath("resources/models/hand.obj");
	fileController->Load();



	/*Window* window2 = manager->NewWindow(422, WINDOW_WIDTH, WINDOW_HEIGHT, 400, 400, "Test Window2", window);
	window2->SetBackgroundColor(0.60f, 0.55f, 0.45f, 1.00f);
	MeshRenderer* meshRenderer2 = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	meshRenderer2->Init();
	meshRenderer2->SetLightType(LightType::POINT_LIGHT);
	meshRenderer2->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshRenderer2->SetRenderMode(RenderMode::WIREFRAME);
	MeshDialog* meshDialog2 = new MeshDialog(1422);
	meshDialog2->SetMeshRenderer(meshRenderer);
	FileController* fileController2 = new FileController(meshRenderer2);
	window2->AddDialog(meshDialog2);
	CameraController* cameraController2 = new CameraController(meshRenderer2);
	window2->AddMouseListener(cameraController2);
	window2->AddWindowListener(cameraController2);
	fileController2->SetPath("Models\\dolphin.obj");
	fileController2->Load();*/

	//-----------------------
	/*Window* window2 = manager->NewWindow(422, WINDOW_WIDTH, WINDOW_HEIGHT, 400, 400, "Test Window2", window);
	window2->SetBackgroundColor(0.60f, 0.55f, 0.45f, 1.00f);
	MeshDialog* meshDialog2 = new MeshDialog(1422);
	meshDialog2->SetMeshRenderer(meshRenderer);
	window2->AddDialog(meshDialog2);

	window2->AddDialog(meshEditorDialog3);*/

	//CameraController* cameraController2 = new CameraController(meshRenderer);
	//window2->AddMouseListener(cameraController2);
	//window2->AddWindowListener(cameraController2);
	//--------------------------

	/*MeshRenderer* meshRenderer2 = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	meshRenderer2->Init();
	meshRenderer2->SetLightType(LightType::POINT_LIGHT);
	meshRenderer2->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshRenderer2->SetRenderMode(RenderMode::WIREFRAME);*/

	//meshRenderer->Init();
	/*MeshRenderer* meshRenderer2 = new MeshRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	meshRenderer2->Init();*/

	// Start application
	manager->Start();

    return 0;
}
