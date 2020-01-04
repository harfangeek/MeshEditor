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

		/* Add the given MeshRenderer to the scene and initialize it for the given context. 
		*  Must be called with the right GL context made current.
		* 
		*  This class supports shared GL context (multiple GL context sharing the same objects).
		*  It is useful when you want to draw the same objects into multiple windows but you're forced 
		*  to have a separate GL context for each window.
		*
		*  The context parameter in an abstract identifier to identify the current OpenGL context.
		*  The user has to maintain a relationship with this identifier and the right GL context.
		*
		*  If you need to initalize the MeshRenderer for additionnal shared GL context, you
		*  can juste wait for the first call to MeshRenderer::Display(), or do it manually calling
		*  MeshRenderer::InitForContext(context)
		*/
		void AddMeshRenderer(MeshRenderer* renderer, unsigned int context=0);

		/* Initialize all scene objects for an additionnal shared GL context.
		*  Must be called with the right GL context made curent.
		*/
		void InitForContext(unsigned int context);

		void Display(unsigned int context = 0, Camera* pCamera = nullptr);
		
		void SetCamera(Camera* camera);
		void SetLight(Light* light);

		const std::vector<MeshRenderer*>& GetMeshRenderers();
		Camera* GetCamera();
		Light* GetLight();

	private:
		std::vector<MeshRenderer*> meshRenderers;
		Camera* camera;
		Light* light;

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
