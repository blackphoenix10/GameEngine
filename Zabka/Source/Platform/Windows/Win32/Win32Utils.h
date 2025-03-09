#pragma once

#define DEFAULTWIDTH 1024
#define DEFAULTHEIGHT 720

namespace Win32 {

	
	
	enum WindowType : DWORD {
		STATIC		=	WS_OVERLAPPED,
		RESIZABLE	=	WS_SIZEBOX,
		POPUP		=	WS_POPUP
	};



	namespace Utils {

		BOOL ZABKA_API AddBitmap(CONST WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);
	}
}