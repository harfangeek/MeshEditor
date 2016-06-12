#pragma once

#include "GUI\Model\Event.h"
#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		class EventListener;

		// This interface allow a subclass to emit events to all attached EventListener objects
		class EventDispatcher
		{
		public:
			// Respectively attach and detach a listener, send a notification to the given listener if notify == true
			// notify need to be true except if the method is called by an EventListener itself
			void Attach(GUI::Interfaces::EventListener* listener, bool notify=true);
			void Detach(GUI::Interfaces::EventListener* listener, bool notify=true);
			// Detach all listeners, send a notification to each listener
			void DetachAll();

		protected:
			// To prevent instanciation of the interface
			EventDispatcher();
			// Automatically detach all listeners when the object is destroyed
			virtual ~EventDispatcher();

			// Send an event to all listeners
			virtual void Notify(GUI::Model::Event* event);

			// List of listeners currently attached to this dispatcher
			std::vector<GUI::Interfaces::EventListener*> listeners;
		};
	}
}