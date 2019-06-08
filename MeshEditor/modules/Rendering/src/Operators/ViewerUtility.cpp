#include "Rendering/ViewerUtility.h"
#include "Rendering/Mesh.h"
#include "Rendering/Vertex.h"
#include "Rendering/MeshRenderer.h"
#include "GUI/Window.h"

#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"

using namespace Rendering;

/*
// Dummy version of vertex selection. "Render" each point to get the position on screen and compare it to the mouse position.
void ViewerUtility::GetSelectedVertices(Rendering::Core::MeshRenderer* renderer, GUI::Interfaces::Window* window, int x, int y, std::vector<unsigned int> &selectedVertices, float precision)
{
	float fovy = renderer->GetFovy();
	int viewportWidth = renderer->GetViewportWidth();
	int viewportHeight = renderer->GetViewportHeight();
	int windowWidth = window->GetWidth();
	int windowHeight = window->GetHeight();
	float zNear = renderer->GetZNear();
	float zFar = renderer->GetZFar();
	glm::vec3 cameraEye = renderer->GetCameraEye();
	glm::vec3 cameraUp = renderer->GetCameraUp();
	glm::vec3 cameraForward = renderer->GetCameraForward();

	float xNorm = (float)x / (float)windowWidth * 2.0f - 1.0f;
	float yNorm = -((float)y / (float)windowHeight * 2.0f - 1.0f);

	glm::mat4 projection_matrix = glm::perspective(fovy, (float)viewportWidth / (float)viewportHeight, zNear, zFar);
	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);

	Mesh* mesh = renderer->GetMesh();
	float d = 0.0;
	glm::vec4 vertexPosition3D, vertexPositionView, vertexPosition2D;
	for (unsigned int i = 0; i < mesh->vertices.size(); i++)
	{
		vertexPosition3D = glm::vec4(mesh->vertices[i]->position.x, mesh->vertices[i]->position.y, mesh->vertices[i]->position.z, 1.0);
		vertexPositionView = view_matrix * vertexPosition3D;
		vertexPosition2D = projection_matrix * vertexPositionView;

		vertexPosition2D = vertexPosition2D / vertexPosition2D.w;
		
		d = sqrtf(powf(vertexPosition2D.x - xNorm, 2) + powf(vertexPosition2D.y - yNorm, 2));
		if (d < precision)
			selectedVertices.push_back(i);
	}
}*/

void ViewerUtility::GetSelectedVertices(MeshRenderer* renderer, GUI::Window* window, int x, int y, std::vector<unsigned int> &selectedVertices, float precision)
{
	// Get all viewer data
	float fovy = renderer->GetFovy();
	auto viewportWidth = static_cast<float>(renderer->GetViewportWidth());
	auto viewportHeight = static_cast<float>(renderer->GetViewportHeight());
	auto windowWidth = static_cast<float>(window->GetWidth());
	auto windowHeight = static_cast<float>(window->GetHeight());
	float zNear = renderer->GetZNear();
	float zFar = renderer->GetZFar();
	glm::vec3 cameraEye = renderer->GetCameraEye();
	glm::vec3 cameraUp = renderer->GetCameraUp();
	glm::vec3 cameraForward = renderer->GetCameraForward();

	// Compute projection and view matrices
	glm::mat4 projection_matrix = glm::perspective(fovy, viewportWidth / viewportHeight, zNear, zFar);
	glm::mat4 view_matrix = glm::lookAt(cameraEye, cameraEye + cameraForward, cameraUp);

	// Normalize mouse position to [-1.0,1.0]
	float xNorm = static_cast<float>(x) / windowWidth * 2.0f - 1.0f;
	float yNorm = -(static_cast<float>(y) / windowHeight * 2.0f - 1.0f);
	
	// Compute the seletion ray. First set it to mouse position as x and y and -1 to z (looking forward)
	glm::vec4 homogeneousRay(xNorm, yNorm, -1.0f, 1.0f);
	// Reverse the projection
	glm::vec4 cameraRay = glm::inverse(projection_matrix) * homogeneousRay;
	cameraRay.z = -1.0f;
	cameraRay.w = 0.0f;
	// Reverse the view matrix
	glm::vec4 worldRay = glm::inverse(view_matrix) * cameraRay;
	glm::vec3 selectionRay = glm::normalize(glm::vec3(worldRay.x, worldRay.y, worldRay.z));

	// Loop over all vertices
	Mesh* mesh = renderer->GetMesh();
	float delta = 0.0f;
	glm::vec3 vertexRay;
	for (unsigned int i = 0; i < mesh->vertices.size(); i++)
	{
		// Compute the vertex position from the camera and "compare" it to the selection ray using dot product
		vertexRay = glm::normalize(mesh->vertices[i]->position - cameraEye);
		delta = glm::abs(glm::dot(vertexRay, selectionRay));
		if (delta >= 1.0 - precision)
			selectedVertices.push_back(i);
	}
}
