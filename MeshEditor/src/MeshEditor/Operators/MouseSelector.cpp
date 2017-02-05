#include "MeshEditor\Operators\MouseSelector.h"
#include "GUI\Model\MouseEvent.h"
#include "GUI\Interfaces\Mouse.h"
#include "Rendering\Operators\ViewerUtility.h"
#include <vector>

using namespace Rendering::Core;
using namespace Rendering::Operators;
using namespace MeshEditor::Operators;
using namespace GUI::Model;
using namespace GUI::Interfaces;
using namespace std;

MouseSelector::MouseSelector(Rendering::Core::MeshRenderer* meshRenderer) : EventListener(), meshRenderer(meshRenderer)
{

}

MouseSelector::~MouseSelector()
{

}

void MouseSelector::OnEvent(const GUI::Model::Event* event)
{
	if (event->msgType == MessageType::MOUSE)
	{
		MouseEvent* mouseEvent = (MouseEvent*)event;
		Mouse* mouse = (Mouse*)event->src;
		if (mouseEvent->msg == MouseMessage::MOUSE_MOVE)
		{
			vector<unsigned int> vertices;
			meshRenderer->ClearVertexSelection();
			ViewerUtility::GetSelectedVertices(meshRenderer, mouseEvent->window, mouse->GetX(), mouse->GetY(), vertices);
			for (unsigned int i = 0; i < vertices.size(); i++)
			{
				meshRenderer->SetVertexSelected(vertices[i], true);
			}

			mouseEvent->window->Render();
		}
	}
}