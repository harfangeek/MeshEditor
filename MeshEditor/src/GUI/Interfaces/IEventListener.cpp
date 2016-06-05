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
	DetachAll();
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
		std::vector<IEventDispatcher*>::iterator dispatcherIt = std::find(dispatchers.begin(), dispatchers.end(), dispatcher);
		if (dispatcherIt != dispatchers.end())
			dispatchers.erase(dispatcherIt, dispatcherIt);
	}
}

void IEventListener::DetachAll()
{
	for (std::vector<IEventDispatcher*>::iterator it = dispatchers.begin(); it != dispatchers.end(); it++)
		(*it)->Detach(this);

	dispatchers.clear();
}
