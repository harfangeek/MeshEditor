#include "GUI/Dialog.h"
#include "GUI/Panel.h"

using namespace GUI;

Dialog::Dialog(unsigned int id, std::string title, float x, float y, float width, float height) : id(id), title(title), x(x), y(y), width(width), height(height)
{
}

Dialog::~Dialog()
{
}

void Dialog::SetPanel(Panel* panel)
{
	this->panel = panel;
}
