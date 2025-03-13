#include "Zabka.h"
#include "Window.h"

namespace Win32 {
	Window::Window(std::wstring title, HICON icon, WindowType type)
		: Win32::SubObject(title, title, icon), m_Type(type)
	{
		Size(DEFAULTWIDTH, DEFAULTHEIGHT);
	}

	Window::~Window() 
	{

	}

	VOID Window::Initialize()
	{
		DWORD style = WindowType::POPUP;

		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);

		RECT R = { 0, 0, Size().cx, Size().cy};
		AdjustWindowRect(&R, m_Type, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		Handle(CreateWindow(Class().c_str(), Title().c_str(),
			m_Type, ((desktop.right / 2) - (Size().cx / 2)), ((desktop.bottom / 2) - (Size().cy / 2)), Size().cx, Size().cy, 0, 0, HInstance(), (void*)this));
		
		ShowWindow(Handle(), SW_SHOW);
		UpdateWindow(Handle());

	}

}
