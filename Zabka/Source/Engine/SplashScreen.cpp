#include "Zabka.h"
#include "SplashScreen.h"

#include "Platform/Windows/Win32/Win32Utils.h"

namespace SplashScreen {

	#define WM_OUTPUTMESSAGE (WM_USER + 0x0001)

	SplashWindow* m_SplashWindow;

	VOID Open()
	{
		if (m_SplashWindow != nullptr)
			return;
		m_SplashWindow = new SplashWindow();
	}

	VOID Close()
	{
		return VOID ZABKA_API();
	}

	VOID AddMessage(const WCHAR* message)
	{
		PostMessage(m_SplashWindow->Handle(), WM_OUTPUTMESSAGE, (WPARAM)message, 0);
	}
}

SplashWindow::SplashWindow()
	: Win32::Window(L"SplashScreen", NULL, Win32::WindowType::POPUP)
{
	wcscpy_s(m_outputMessage, L"SplashScreen Starting...");
	Win32::Window::RegisterNewClass();
	Size(800, 600);
	Win32::Window::Initialize();

}

SplashWindow::~SplashWindow()
{
}

