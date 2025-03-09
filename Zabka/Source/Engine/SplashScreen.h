#pragma once

#include "Platform/Windows/Win32/Window.h"

namespace SplashScreen {


	VOID ZABKA_API Open();
	VOID ZABKA_API Close();
	VOID ZABKA_API AddMessage(CONST WCHAR* message);

}

class ZABKA_API SplashWindow : public Win32::Window {

public:
	SplashWindow();
	~SplashWindow();

	virtual LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	WCHAR m_outputMessage[MAX_NAME_STRING];
};