#pragma once

#include "GUI\Model\Event.h"
#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		class IEventListener;

		class IEventDispatcher
		{
		public:
			void Attach(GUI::Interfaces::IEventListener* listener);
			void Detach(GUI::Interfaces::IEventListener* listener);
			void DetachAll();

		protected:
			IEventDispatcher();
			virtual ~IEventDispatcher();

			virtual void Notify(GUI::Model::Event* event);

			std::vector<GUI::Interfaces::IEventListener*> listeners;
		};
	}
}