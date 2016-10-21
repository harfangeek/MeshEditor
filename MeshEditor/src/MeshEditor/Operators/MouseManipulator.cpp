#include "MeshEditor\Operators\MouseManipulator.h"
#include "GUI\Model\MouseEvent.h"
#include "GUI\Interfaces\Mouse.h"

using namespace Rendering::Core;
using namespace MeshEditor::Operators;
using namespace GUI::Model;
using namespace GUI::Interfaces;

MouseManipulator::MouseManipulator(Rendering::Core::MeshRenderer* meshRenderer) : EventListener(), meshRenderer(meshRenderer)
{

}

MouseManipulator::~MouseManipulator()
{

}

void MouseManipulator::OnEvent(const GUI::Model::Event* event)
{
	static int i = 0;

	if (event->msgType == MessageType::MOUSE)
	{
		MouseEvent* mouseEvent = (MouseEvent*)event;
		Mouse* mouse = (Mouse*)event->src;
		if (mouseEvent->msg == MouseMessage::MOUSE_MOVE)
		{
			float dx = (float)mouseEvent->dx / (float)mouseEvent->window->GetWidth();
			float dy = (float)mouseEvent->dy / (float)mouseEvent->window->GetHeight();
			if (mouse->IsButtonPressed(MouseButton::LEFT_BUTTON))
			{
				meshRenderer->Rotate(dx, dy);
				mouseEvent->window->Render();
			}
			else if (mouse->IsButtonPressed(MouseButton::MIDDLE_BUTTON))
			{
				meshRenderer->Translate(-dx * 5.0f, dy * 5.0f);
				mouseEvent->window->Render();
			}
		}
		else if (mouseEvent->msg == MouseMessage::WHEEL_SCROLL)
		{
			meshRenderer->Zoom((float)mouseEvent->wheel * 0.1);
			mouseEvent->window->Render();
		}
		else if (mouseEvent->msg == MouseMessage::BUTTON_PRESSED && mouseEvent->button == MouseButton::RIGHT_BUTTON)
		{
			meshRenderer->SetVertexSelected(i, false);
			i = (i + 1) % 8;
			meshRenderer->SetVertexSelected(i, true);
			mouseEvent->window->Render();
		}
	}
}