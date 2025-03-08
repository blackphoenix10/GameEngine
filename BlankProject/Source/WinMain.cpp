#include <windows.h>

	#define		MAX_NAME_STRING 256
	#define		HInstance() GetModuleHandle(NULL)

	WCHAR		WindowClass[MAX_NAME_STRING];
	WCHAR		WindowTitle[MAX_NAME_STRING];

	INT			WindowHeight;
	INT			WindowWidth;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

	// Initialise Global Vatiables

	wcscpy_s(WindowClass, TEXT("TutorialOneClass"));
	wcscpy_s(WindowTitle, TEXT("Our First Window"));
	WindowWidth = 1366;
	WindowHeight = 768;


	// Create window class

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);


	// Create and display out window

	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);


	// listen for message events

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}