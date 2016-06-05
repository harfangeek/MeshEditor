#include "GUI\Interfaces\IEventDispatcher.h"
#include "GUI\Interfaces\IEventListener.h"
#include <algorithm>

using namespace GUI;
using namespace GUI::Interfaces;

IEventDispatcher::IEventDispatcher()
{
}

IEventDispatcher::~IEventDispatcher()
{
	DetachAll();
}

void IEventDispatcher::Attach(IEventListener* listener, bool notify)
{
	if (listener != NULL)
	{
		listeners.push_back(listener);
		if(notify)
			listener->OnAttach(this); // Notify the listener
	}
}

void IEventDispatcher::Detach(IEventListener* listener, bool notify)
{
	if (listener != NULL)
	{
		// If the listener was effectively attached to this dispatcher
		std::vector<IEventListener*>::iterator listenerIt = std::find(listeners.begin(), listeners.end(), listener);
		if (listenerIt != listeners.end())
		{
			if (notify)
				(*listenerIt)->OnDetach(this); // Notify the listener
			listeners.erase(listenerIt, listenerIt);
		}
	}
}

void IEventDispatcher::DetachAll()
{
	for (std::vector<IEventListener*>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)->OnDetach(this);

	listeners.clear();
}

void IEventDispatcher::Notify(Model::Event* event)
{
	for (std::vector<IEventListener*>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)->OnEvent(this, event);
}
