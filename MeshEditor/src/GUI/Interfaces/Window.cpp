#include "GUI/Interfaces/Window.h"
#include "GUI/Interfaces/Dialog.h"
#include "GUI/Interfaces/MouseListener.h"
#include "GUI/Interfaces/WindowListener.h"

#include <algorithm>

using namespace GUI::Interfaces;

Window::Window(unsigned int id, unsigned int width, unsigned int height, int x, int y, std::string title)
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

void Window::GetBackgroundColor(float &r, float &g, float &b, float &a)
{
	r = this->r;
	g = this->g;
	b = this->b;
	a = this->a;
}

void Window::Resize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
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

void Window::SetBackgroundColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Window::AddDialog(GUI::Interfaces::Dialog* dialog)
{
	dialogs.push_back(dialog);
}

void Window::Display()
{
	for (auto dialog : dialogs)
		dialog->Display();
}

void Window::AddMouseListener(GUI::Interfaces::MouseListener* listener)
{
	auto it = std::find(mouseListeners.begin(), mouseListeners.end(), listener);	
	if (it == mouseListeners.end())
		mouseListeners.push_back(listener);
}

void Window::NotifyMouseButtonEvent(double x, double y, int button, int action, int mods)
{
	for (auto listener : mouseListeners)
		listener->OnMouseButtonEvent(this, x, y, button, action, mods);

	mousex = x;
	mousey = y;
}

void Window::NotifyMouseMoveEvent(double x, double y)
{
	for (auto listener : mouseListeners)
		listener->OnMouseMoveEvent(this, x, y, x - mousex, y - mousey);

	mousex = x;
	mousey = y;
}

void Window::NotifyMouseScrollEvent(double dx, double dy)
{
	for (auto listener : mouseListeners)
		listener->OnMouseScrollEvent(this, dx, dy);
}

void Window::RemoveMouseListener(GUI::Interfaces::MouseListener* listener)
{
	auto it = std::find(mouseListeners.begin(), mouseListeners.end(), listener);
	if (it != mouseListeners.end())
		mouseListeners.erase(it);
}

void Window::AddWindowListener(GUI::Interfaces::WindowListener* listener)
{
	auto it = std::find(windowListeners.begin(), windowListeners.end(), listener);
	if (it == windowListeners.end())
		windowListeners.push_back(listener);
}

void Window::NotifyWindowResizedEvent(int width, int height)
{
	for (auto listener : windowListeners)
		listener->OnWindowResizedEvent(this, width, height);
}

void Window::RemoveWindowListener(GUI::Interfaces::WindowListener* listener)
{
	auto it = std::find(windowListeners.begin(), windowListeners.end(), listener);
	if (it == windowListeners.end())
		windowListeners.erase(it);
}

