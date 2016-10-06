#include "GUI\Model\WindowEvent.h"
#include "GUI\Interfaces\Window.h"

using namespace GUI::Model;
using namespace GUI::Interfaces;

WindowEvent::WindowEvent(GUI::Interfaces::Window* window, WindowMessages msg) : Event(window, MessageType::WINDOW),
						 													    windowId(window->GetId()),
																				width(window->GetWidth()),
																				height(window->GetHeight()),
																				prevWidth(window->GetWidth()),
																				prevHeight(window->GetWidth()),
																				timeSinceLastFrame(window->GetTimeSinceLastFrame())
{
}
