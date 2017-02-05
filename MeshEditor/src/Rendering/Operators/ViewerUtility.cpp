#include "Rendering\Operators\ViewerUtility.h"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtx\rotate_vector.hpp"

#include <iostream>

using namespace Rendering::Core;
using namespace Rendering::Model;
using namespace Rendering::Operators;

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

	// Normaliser position de la souris de -1.0 à 1.0
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
		//vertexPosition2D.w = -vertexPositionView.z;

		vertexPosition2D = vertexPosition2D / vertexPosition2D.w;
		
		d = sqrtf(powf(vertexPosition2D.x - xNorm, 2) + powf(vertexPosition2D.y - yNorm, 2));
		if (d < precision)
			selectedVertices.push_back(i);

		if (i == 0 || i == 6)
		{
			std::cout << vertexPosition3D.x << " : " << vertexPosition3D.y << " : " << vertexPosition3D.z << " : " << vertexPosition3D.w << std::endl;
			std::cout << vertexPositionView.x << " : " << vertexPositionView.y << " : " << vertexPositionView.z << " : " << vertexPositionView.w << std::endl;
			std::cout << vertexPosition2D.x << " : " << vertexPosition2D.y << " : " << vertexPosition2D.z << " : " << vertexPosition2D.w << std::endl;
			std::cout << xNorm <<  " : " << yNorm << std::endl;
			std::cout << d << std::endl << std::endl;
		}
	}
}
