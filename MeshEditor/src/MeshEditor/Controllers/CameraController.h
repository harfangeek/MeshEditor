#pragma once

#include "GUI/Interfaces/MouseListener.h"
#include "GUI/Interfaces/WindowListener.h"
#include "Rendering/Core/MeshRenderer.h"

namespace MeshEditor
{
	namespace Controllers
	{
		class CameraController : public GUI::Interfaces::MouseListener,
								 public GUI::Interfaces::WindowListener
		{
		public:
			CameraController(Rendering::Core::MeshRenderer* meshRenderer);
			virtual ~CameraController();

			virtual void OnMouseButtonEvent(GUI::Interfaces::Window* window, double x, double y, int button, int action, int mods);
			virtual void OnMouseMoveEvent(GUI::Interfaces::Window* window, double x, double y, double dx, double dy);
			virtual void OnMouseScrollEvent(GUI::Interfaces::Window* window, double dx, double dy);
			virtual void OnWindowResizedEvent(GUI::Interfaces::Window* window, int width, int height);

		private:
			bool translate;
			bool rotate;
			Rendering::Core::MeshRenderer* meshRenderer;
		};
	}
}