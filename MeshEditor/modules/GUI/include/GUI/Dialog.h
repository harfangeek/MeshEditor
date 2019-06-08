#pragma once

#include <string>

namespace GUI
{
	class Panel;

	class Dialog
	{
	public:
		Dialog(unsigned int id, std::string title, float x, float y, float width, float height);
		virtual ~Dialog();

		virtual void SetPanel(Panel* panel);
		virtual void Display() =0;

	protected:
		unsigned int id;
		std::string title;
		float x;
		float y;
		float width;
		float height;
		Panel* panel;
	};
}