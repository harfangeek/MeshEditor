#pragma once

#include "GUI\Model\Event.h"
#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		class IEventDispatcher;

		// This interface allow a subclass to receive events emitted by one or several IEventDispatcher objects
		class IEventListener
		{
		public:
			// Called respectively when an IEventListener is attached to and detached from an IEventDispatcher
			// The interface need to remember which IEventDispatcher is attached to in order 
			// to detach from its automatically when the object is destroyed, avoiding an IEventDispatcher to
			// send an event to a deleted object
			void OnAttach(GUI::Interfaces::IEventDispatcher* dispatcher);			
			void OnDetach(GUI::Interfaces::IEventDispatcher* dispatcher);
			// Called when an event is send by a dispatcher. Need to be implemented by subclasses
			virtual void OnEvent(GUI::Interfaces::IEventDispatcher* source, GUI::Model::Event* event) = 0;

		protected:
			// To prevent instanciation of the interface
			IEventListener();
			// Automatically detach this listener from all dispatcher it is attached to
			virtual ~IEventListener();

			// Detach this listener from all dispatchers it is attached to
			void DetachFromAll();

			std::vector<GUI::Interfaces::IEventDispatcher*> dispatchers; // List of all dispatchers this listener is attached to
		};
	}
}