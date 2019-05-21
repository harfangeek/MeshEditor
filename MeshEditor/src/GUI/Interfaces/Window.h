#pragma once



#include <string>
#include <vector>

namespace GUI
{
	namespace Interfaces
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
			virtual void AddDialog(GUI::Interfaces::Dialog* dialog);

			void AddMouseListener(GUI::Interfaces::MouseListener* listener);
			void NotifyMouseButtonEvent(double x, double y, int button, int action, int mods);
			void NotifyMouseMoveEvent(double x, double y);
			void NotifyMouseScrollEvent(double dx, double dy);
			void RemoveMouseListener(GUI::Interfaces::MouseListener* listener);

			void AddWindowListener(GUI::Interfaces::WindowListener* listener);
			void NotifyWindowResizedEvent(int width, int height);
			void RemoveWindowListener(GUI::Interfaces::WindowListener* listener);

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
			std::vector<GUI::Interfaces::Dialog*> dialogs;
			std::vector<GUI::Interfaces::MouseListener*> mouseListeners;
			std::vector<GUI::Interfaces::WindowListener*> windowListeners;
		};
	}
}
