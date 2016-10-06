#include "GUI\Model\Event.h"
#include "GUI\Interfaces\EventDispatcher.h"

using namespace GUI;
using namespace GUI::Model;

Event::Event(GUI::Interfaces::EventDispatcher* src, MessageType msgType) : src(src), msgType(msgType)
{
}

Event::~Event()
{

}