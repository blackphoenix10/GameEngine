#include "Zabka.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"

namespace Zabka {

	Simulation::Simulation()
		:Win32::Window(L"MainApplication", NULL, Win32::WindowType::RESIZABLE), renderer(nullptr)
	{
	}

	Simulation::~Simulation()
	{
		Cleanup();
	}

	VOID Simulation::PreInitialize()
	{
		Logger::PrintDebugSeperator();
		Logger::PrintLog(L"Application Starting...");
		Logger::PrintLog(L"Game Name: %s", PerGameSettings::GameName());
		Logger::PrintLog(L"Boot Time: %s", Time::GetDateTimeString().c_str());
		Logger::PrintLog(L"Engine Mode: %s", Engine::EngineModeToString().c_str());
		Logger::PrintDebugSeperator();

		SplashScreen::Open();

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();

		renderer = new DirectX12Renderer(Handle());
		if (!renderer->Initialize()) {
			Logger::PrintLog(L"Failed to initialize DirectX12Renderer");
		}
	}

	VOID Simulation::Run()
	{
		Logger::PrintLog(L"Running Simulation");
		if (renderer) {
			renderer->Render();
		}
	}

	VOID Simulation::Cleanup()
	{
		if (renderer) {
			delete renderer;
			renderer = nullptr;
			Logger::PrintLog(L"Simulation cleaned up");
		}
	}

	LRESULT Simulation::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case NULL:
			break;
		default:
			break;
		}
		return CommonMessageHandler(hwnd, message, wParam, lParam);
	}
}