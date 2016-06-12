#include "GUI\Interfaces\EventListener.h"
#include "GUI\Interfaces\EventDispatcher.h"
#include <algorithm>

using namespace GUI;
using namespace Interfaces;

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	DetachFromAll();
}

void EventListener::OnAttach(EventDispatcher* dispatcher)
{
	if (dispatcher != NULL)
		dispatchers.push_back(dispatcher);
}

void EventListener::OnDetach(EventDispatcher* dispatcher)
{
	if (dispatcher != NULL)
	{
		// If this listener is effectively attached to the given dispatcher
		std::vector<EventDispatcher*>::iterator dispatcherIt = std::find(dispatchers.begin(), dispatchers.end(), dispatcher);
		if (dispatcherIt != dispatchers.end())
			dispatchers.erase(dispatcherIt, dispatcherIt);
	}
}

void EventListener::DetachFromAll()
{
	for (std::vector<EventDispatcher*>::iterator it = dispatchers.begin(); it != dispatchers.end(); it++)
		(*it)->Detach(this, false); // Don't need a notification since the listener call detach itself

	dispatchers.clear();
}
