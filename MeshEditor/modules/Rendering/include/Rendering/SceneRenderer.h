#pragma once

#include <vector>
#include "GL/gl3w.h"

namespace Rendering
{
	class MeshRenderer;
	class Light;
	class Camera;

	class SceneRenderer
	{
	public:
		SceneRenderer(Camera* camera, Light* light);
		~SceneRenderer();

		void Display(Camera* pCamera=nullptr);

		void AddMeshRenderer(MeshRenderer* renderer);
		void SetCamera(Camera* camera);
		void SetLight(Light* light);

		const std::vector<MeshRenderer*>& GetMeshRenderers();
		Camera* GetCamera();
		Light* GetLight();

	private:
		std::vector<MeshRenderer*> meshRenderers;
		Light* light;
		Camera* camera;

		GLuint program; // Shader program

		GLuint projectionMatrixLoc;
		GLuint viewMatrixLoc;

		GLuint lightTypeLoc;
		GLuint lightColorLoc;
		GLuint lightPositionLoc;
		GLuint lightDirectionLoc;
		GLuint lightAngleLoc;

		void InitShader();
		void InitLight();
		void InitCamera();
		void SendLightData();
		void SendCameraData(Camera* pCamera);
	};
}
