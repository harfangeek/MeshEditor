#pragma once

namespace GUI
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