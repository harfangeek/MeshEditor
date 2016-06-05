#include "GUI\Interfaces\IEventListener.h"
#include "GUI\Interfaces\IEventDispatcher.h"
#include <algorithm>

using namespace GUI;
using namespace Interfaces;

IEventListener::IEventListener()
{
}

IEventListener::~IEventListener()
{
	DetachFromAll();
}

void IEventListener::OnAttach(IEventDispatcher* dispatcher)
{
	if (dispatcher != NULL)
		dispatchers.push_back(dispatcher);
}

void IEventListener::OnDetach(IEventDispatcher* dispatcher)
{
	if (dispatcher != NULL)
	{
		// If this listener is effectively attached to the given dispatcher
		std::vector<IEventDispatcher*>::iterator dispatcherIt = std::find(dispatchers.begin(), dispatchers.end(), dispatcher);
		if (dispatcherIt != dispatchers.end())
			dispatchers.erase(dispatcherIt, dispatcherIt);
	}
}

void IEventListener::DetachFromAll()
{
	for (std::vector<IEventDispatcher*>::iterator it = dispatchers.begin(); it != dispatchers.end(); it++)
		(*it)->Detach(this, false); // Don't need a notification since the listener call detach itself

	dispatchers.clear();
}
