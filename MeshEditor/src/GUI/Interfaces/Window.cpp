#include "GUI\Interfaces\Window.h"
#include "GUI\Model\WindowEvent.h"

using namespace GUI::Interfaces;
using namespace GUI::Model;

Window::Window(int id, int width, int height, int x, int y, std::string title)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->title = title;
}

Window::~Window()
{

}

int Window::GetId()
{
	return id;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

int Window::GetX()
{
	return x;
}

int Window::GetY()
{
	return y;
}

std::string Window::GetTitle()
{
	return title;
}

double Window::GetTimeSinceLastFrame()
{
	std::time_t currTime = time(NULL);
	return difftime(currTime, lastFrame);
}

void Window::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
	WindowEvent event(this, WindowMessages::WINDOW_RESIZED);
	Notify(&event);
}

void Window::Move(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Window::SetTitle(std::string title)
{
	this->title = title;
}

void Window::Render()
{
	WindowEvent event(this, WindowMessages::WINDOW_RENDERED);
	Notify(&event);
}
