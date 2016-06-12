#include "GUI\Interfaces\EventDispatcher.h"
#include "GUI\Interfaces\EventListener.h"
#include <algorithm>

using namespace GUI;
using namespace GUI::Interfaces;

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
	DetachAll();
}

void EventDispatcher::Attach(EventListener* listener, bool notify)
{
	if (listener != NULL)
	{
		listeners.push_back(listener);
		if(notify)
			listener->OnAttach(this); // Notify the listener
	}
}

void EventDispatcher::Detach(EventListener* listener, bool notify)
{
	if (listener != NULL)
	{
		// If the listener was effectively attached to this dispatcher
		std::vector<EventListener*>::iterator listenerIt = std::find(listeners.begin(), listeners.end(), listener);
		if (listenerIt != listeners.end())
		{
			if (notify)
				(*listenerIt)->OnDetach(this); // Notify the listener
			listeners.erase(listenerIt, listenerIt);
		}
	}
}

void EventDispatcher::DetachAll()
{
	for (std::vector<EventListener*>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)->OnDetach(this);

	listeners.clear();
}

void EventDispatcher::Notify(Model::Event* event)
{
	for (std::vector<EventListener*>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)->OnEvent(this, event);
}
