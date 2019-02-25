#pragma once

#include "GUI/Interfaces/Panel.h"

namespace GUI
{
	namespace Interfaces
	{
		class Panel
		{
		public:
			Panel(unsigned int id);
			virtual ~Panel();

			virtual void Display() = 0;

		protected:
			unsigned int id;
		};
	}
}