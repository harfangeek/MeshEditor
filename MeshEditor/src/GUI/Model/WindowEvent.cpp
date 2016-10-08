#include "GUI\Model\WindowEvent.h"
#include "GUI\Interfaces\Window.h"

using namespace GUI::Model;
using namespace GUI::Interfaces;

WindowEvent::WindowEvent(GUI::Interfaces::Window* window, 
						 WindowMessages msg, 
						 int prevWidth, 
						 int prevHeight) : Event(window, MessageType::WINDOW),
										   msg(msg),
						 				   windowId(window->GetId()),
										   width(window->GetWidth()),
										   height(window->GetHeight()),
										   prevWidth(prevWidth),
										   prevHeight(prevHeight),
										   timeSinceLastFrame(window->GetTimeSinceLastFrame())
{
	if (msg != WindowMessages::WINDOW_RESIZED)
	{
		this->prevWidth = width;
		this->prevHeight = height;
	}
}
