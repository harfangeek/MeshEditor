#pragma once

#include <string>
#include <vector>

namespace GUI
{
	class Dialog;
	class MouseListener;
	class WindowListener;

	class Window
	{
	public:
		Window(unsigned int id, unsigned int width, unsigned int height, int x, int y, std::string title="");
		virtual ~Window();

		virtual void Resize(unsigned int width, unsigned int height);
		virtual void Move(int x, int y);
		virtual void SetTitle(std::string title);
		virtual void SetBackgroundColor(float r, float g, float b, float a);
		virtual void Display();
		virtual void AddDialog(Dialog* dialog);

		void AddMouseListener(MouseListener* listener);
		void NotifyMouseButtonEvent(double x, double y, int button, int action, int mods);
		void NotifyMouseMoveEvent(double x, double y);
		void NotifyMouseScrollEvent(double dx, double dy);
		void RemoveMouseListener(MouseListener* listener);

		void AddWindowListener(WindowListener* listener);
		void NotifyWindowResizedEvent(int width, int height);
		void RemoveWindowListener(WindowListener* listener);

		int GetId();
		int GetWidth();
		int GetHeight();
		int GetX();
		int GetY();
		std::string GetTitle();
		void GetBackgroundColor(float &r, float &g, float &b, float &a);

	protected:
		int id;
		int width;
		int height;
		int x;
		int y;
		float r, g, b, a;
		double mousex;
		double mousey;
		float lastRender;
		std::string title;
		std::vector<Dialog*> dialogs;
		std::vector<MouseListener*> mouseListeners;
		std::vector<WindowListener*> windowListeners;
	};
}
