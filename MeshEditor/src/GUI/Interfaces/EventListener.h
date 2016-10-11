#pragma once

#include "GUI\Model\Event.h"
#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		class EventDispatcher;

		// This interface allow a subclass to receive events emitted by one or several IEventDispatcher objects
		class EventListener
		{
		public:
			// Called respectively when an IEventListener is attached to and detached from an IEventDispatcher
			// The interface need to remember which IEventDispatcher is attached to in order 
			// to detach from its automatically when the object is destroyed, avoiding an IEventDispatcher to
			// send an event to a deleted object
			void OnAttach(GUI::Interfaces::EventDispatcher* dispatcher);			
			void OnDetach(GUI::Interfaces::EventDispatcher* dispatcher);
			// Called when an event is send by a dispatcher. Need to be implemented by subclasses
			virtual void OnEvent(const GUI::Model::Event* event) = 0;

		protected:
			// To prevent instanciation of the interface
			EventListener();
			// Automatically detach this listener from all dispatcher it is attached to
			virtual ~EventListener();

			// Detach this listener from all dispatchers it is attached to
			void DetachFromAll();

			std::vector<GUI::Interfaces::EventDispatcher*> dispatchers; // List of all dispatchers this listener is attached to
		};
	}
}