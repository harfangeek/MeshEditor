#include "GUI/Interfaces/Dialog.h"
#include "GUI/Interfaces/Panel.h"

using namespace GUI::Interfaces;

Dialog::Dialog(unsigned int id, std::string title, float x, float y, float width, float height) : id(id), title(title), x(x), y(y), width(width), height(height)
{
}

Dialog::~Dialog()
{
}

void Dialog::SetPanel(GUI::Interfaces::Panel* panel)
{
	this->panel = panel;
}
