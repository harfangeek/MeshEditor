#pragma once

#include "GUI/Interfaces/Panel.h"
#include <vector>
#include <string>

namespace GUI
{
	namespace Interfaces
	{
		class Dialog
		{
		public:
			Dialog(unsigned int id, std::string title, float x, float y, float width, float height);
			virtual ~Dialog();

			virtual void SetPanel(GUI::Interfaces::Panel* panel);
			virtual void Display() =0;

		protected:
			unsigned int id;
			std::string title;
			float x;
			float y;
			float width;
			float height;
			GUI::Interfaces::Panel* panel;
		};
	}
}