#include "MeshEditor/ViewerController.h"
#include "Rendering/MeshRenderer.h"

using namespace MeshEditor;
using namespace Rendering;

ViewerController::ViewerController(Rendering::MeshRenderer* meshRenderer) : mesh(true), 
																			wireframe(false), 
																			vertices(false), 
																			facesNormals(false), 
																			verticesNormals(false),
																			meshColor{ 0.0f, 1.0f, 0.0f, 1.0f },
																			wireframeColor{ 0.0, 1.0, 1.0, 0.0 },
																			verticesColor{ 0.0, 0.0, 1.0, 0.0 },
																			facesNormalsColor{ 1.0, 1.0, 0.0, 0.0 },
																			verticesNormalsColor{ 1.0, 0.0, 1.0, 0.0 },
																			meshRenderer(meshRenderer)
{
}

ViewerController::~ViewerController()
{

}

void ViewerController::Update()
{
	if (meshRenderer)
	{
		RenderMode state = RenderMode::None;
		if(mesh)
			state |= RenderMode::Mesh;
		if (wireframe)
			state |= RenderMode::Wireframe;
		if (vertices)
			state |= RenderMode::Vertices;
		if (facesNormals)
			state |= RenderMode::FacesNormals;
		if (verticesNormals)
			state |= RenderMode::VerticesNormals;

		meshRenderer->SetRenderMode(state);
		meshRenderer->SetMeshColor(glm::vec4(meshColor[0], meshColor[1], meshColor[2], meshColor[3]));
		meshRenderer->SetWireframeColor(glm::vec4(wireframeColor[0], wireframeColor[1], wireframeColor[2], wireframeColor[3]));
		meshRenderer->SetVerticesColor(glm::vec4(verticesColor[0], verticesColor[1], verticesColor[2], verticesColor[3]));
		meshRenderer->SetFacesNormalsColor(glm::vec4(facesNormalsColor[0], facesNormalsColor[1], facesNormalsColor[2], facesNormalsColor[3]));
		meshRenderer->SetVerticesNormalsColor(glm::vec4(verticesNormalsColor[0], verticesNormalsColor[1], verticesNormalsColor[2], verticesNormalsColor[3]));
	}
}
