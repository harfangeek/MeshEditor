#include "Rendering/Camera.h"

#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/quaternion.hpp"

//#include "GLM/glm.hpp"

using namespace Rendering;
//using namespace glm;

Camera::Camera(int viewportWidth, int viewportHeight) : viewportWidth(viewportWidth),
														viewportHeight(viewportHeight),
														cameraEye(0, 0, 2),
														cameraUp(0, 1, 0),
														cameraForward(0, 0, -1),
														fovy(45.0f),
														zNear(0.01f),
														zFar(5000.0f)
{
	SetViewPort(viewportWidth, viewportHeight);
}

Camera::~Camera()
{

}

void Camera::SetViewPort(int viewportWidth, int viewportHeight)
{
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
}

void Camera::Rotate(float x, float y)
{
	float theta = 4.0f * (fabs(x) + fabs(y));
	if (theta > 0.00000001)
	{
		glm::vec3 cameraRight = glm::cross(cameraUp, -cameraForward);
		// Compute a vector between (1, 0, 0) (only X rotation) and (0, 1, 0) (only Y rotation)
		// This vector represents the rotation axis combining the two rotations
		glm::vec3 rotationAxis = x * -cameraUp + y * -cameraRight;
		rotationAxis = glm::normalize(rotationAxis);

		cameraForward = glm::rotate(cameraForward, theta, rotationAxis);
		cameraUp = glm::rotate(cameraUp, theta, rotationAxis);
		cameraEye = glm::rotate(cameraEye, theta, rotationAxis);

		cameraUp = glm::normalize(cameraUp);
		//cameraEye = glm::normalize(cameraEye);
		cameraForward = glm::normalize(cameraForward);
	}
}

void Camera::Translate(float x, float y)
{
	glm::vec3 cameraRight = glm::cross(cameraUp, -cameraForward);
	cameraEye += x * cameraRight;
	cameraEye += y * cameraUp;
}

void Camera::Zoom(float value)
{
	cameraEye += value * cameraForward;
}

int Camera::GetViewportWidth()
{
	return viewportWidth;
}

int Camera::GetViewportHeight()
{
	return viewportHeight;
}

float Camera::GetFovy()
{
	return fovy;
}

float Camera::GetZNear()
{
	return zNear;
}

float Camera::GetZFar()
{
	return zFar;
}

glm::vec3 Camera::GetCameraEye()
{
	return cameraEye;
}

glm::vec3 Camera::GetCameraUp()
{
	return cameraUp;
}

glm::vec3 Camera::GetCameraForward()
{
	return cameraForward;
}
