#pragma once

#include "GUI\Model\Event.h"
#include <vector>

namespace GUI
{
	namespace Interfaces
	{
		class IEventDispatcher;

		class IEventListener
		{
		public:
			void OnAttach(GUI::Interfaces::IEventDispatcher* dispatcher);
			void OnDetach(GUI::Interfaces::IEventDispatcher* dispatcher);
			virtual void OnEvent(GUI::Interfaces::IEventDispatcher* source, GUI::Model::Event* event) = 0;

		protected:
			IEventListener();
			virtual ~IEventListener();

			void DetachAll();

			std::vector<GUI::Interfaces::IEventDispatcher*> dispatchers;
		};
	}
}