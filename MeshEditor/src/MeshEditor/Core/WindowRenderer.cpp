#include "MeshEditor\Core\WindowRenderer.h"
#include "GUI\Model\WindowEvent.h"

using namespace MeshEditor::Core;
using namespace GUI::Model;

WindowRenderer::WindowRenderer(Rendering::Core::MeshRenderer* meshRenderer) : meshRenderer(meshRenderer)
{
}

void WindowRenderer::OnEvent(GUI::Interfaces::EventDispatcher* source, const GUI::Model::Event* event)
{
	if (event->msgType == MessageType::WINDOW && meshRenderer)
	{
		WindowEvent* winEvent = (WindowEvent*)event;
		if (winEvent->msg == WindowMessages::WINDOW_RENDERED)
			meshRenderer->Display();
		else if (winEvent->msg == WindowMessages::WINDOW_RESIZED)
			meshRenderer->SetViewPort(winEvent->width, winEvent->height);
	}
}