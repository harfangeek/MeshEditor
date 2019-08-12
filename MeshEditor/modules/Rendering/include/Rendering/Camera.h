#pragma once

#include "GLM/glm.hpp"

namespace Rendering
{
	class Camera
	{
	public:		
		Camera(int viewportWidth, int viewportHeight);
		~Camera();

		int GetViewportWidth();
		int GetViewportHeight();
		float GetFovy();
		float GetZNear();
		float GetZFar();
		glm::vec3 GetCameraEye();
		glm::vec3 GetCameraUp();
		glm::vec3 GetCameraForward();

		glm::vec3 cameraRotation;
		glm::vec3 cameraPosition;

		void SetViewPort(int viewportWidth, int viewportHeight);
		void Rotate(float x, float y); // Rotate the camera around the x axis by x degrees and around the y axis by y degrees
		void Translate(float x, float y);
		void Zoom(float value);

	private:
		glm::vec3 cameraEye; // Position of the camera
		glm::vec3 cameraUp; // Camera orientation
		glm::vec3 cameraForward; // Camera direction

		int viewportWidth;
		int viewportHeight;
		float fovy;
		float zNear;
		float zFar;
	};
}
