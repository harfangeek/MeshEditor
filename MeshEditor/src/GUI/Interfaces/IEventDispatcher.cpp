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

void IEventDispatcher::Attach(IEventListener* listener)
{
	if (listener != NULL)
	{
		listeners.push_back(listener);
		listener->OnAttach(this);
	}
}

void IEventDispatcher::Detach(IEventListener* listener)
{
	if (listener != NULL)
	{
		std::vector<IEventListener*>::iterator listenerIt = std::find(listeners.begin(), listeners.end(), listener);
		if (listenerIt != listeners.end())
		{
			(*listenerIt)->OnDetach(this);
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
