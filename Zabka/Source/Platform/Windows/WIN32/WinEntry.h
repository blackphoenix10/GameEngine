#include "Zabka.h"
#include "IApplication.h"
#include "Common/CmdLineArgs.h"

extern Win32::IApplication* EntryApplication();

_Use_decl_annotations_
INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
    auto EntryApp = EntryApplication();

    PerGameSettings GameSettings;
    EntryApp->SetupPerGameSettings();

    CmdLineArgs::ReadArguments();

    Logger logger;

    EntryApp->PreInitialize();

    EntryApp->Initialize();

    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            EntryApp->Update();
        }
    }

    return 0;
}
