#pragma once

#include "Platform/Windows/Win32/Window.h"

namespace SplashScreen {


	VOID ZABKA_API Open();
	VOID ZABKA_API Close();
	VOID ZABKA_API AddMessage(CONST WCHAR* message);

}

class SplashWindow : public Win32::Window {

public:
	ZABKA_API SplashWindow();
	ZABKA_API ~SplashWindow();

	virtual LRESULT ZABKA_API MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override
	{

		switch (message)
		{
		case WM_PAINT:
		{
			// HBITMAP hbitmap;
			HDC hdc; //, hmemdc;
			PAINTSTRUCT ps;

			hdc = BeginPaint(hwnd, &ps);

			Win32::Utils::AddBitmap(PerGameSettings::SplashUrl(), hdc);

			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(34, 139, 34));

			if (Engine::GetMode() != Engine::EngineMode::RELEASE) {

				std::wstring engineModeText = Engine::EngineModeToString() + L" Mode";
				SetTextAlign(hdc, TA_RIGHT);
				TextOut(hdc, Size().cx - 15, 15, engineModeText.c_str(), (INT)wcslen(engineModeText.c_str()));

			}

			SetTextAlign(hdc, TA_CENTER);

			TextOut(hdc, Size().cx / 2, Size().cy - 30, m_outputMessage, (INT)wcslen(m_outputMessage));
			EndPaint(hwnd, &ps);
		}
		break;
		case WM_OUTPUTMESSAGE:
		{
			WCHAR* msg = (WCHAR*)wParam;
			wcscpy_s(m_outputMessage, msg);
			RedrawWindow(Handle(), NULL, NULL, RDW_INVALIDATE);
			return 0;
		}
		}

		return CommonMessageHandler(hwnd, message, wParam, lParam);
	}

private:
	WCHAR m_outputMessage[MAX_NAME_STRING];
};