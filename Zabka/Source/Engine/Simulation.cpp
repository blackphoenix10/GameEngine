#include "Zabka.h"
#include "Simulation.h"
#include "Engine/SplashScreen.h"


namespace Zabka {

	Zabka::Simulation::Simulation()
		:Win32::Window(L"MainApplication", NULL, Win32::WindowType::RESIZABLE)
	{

	}

	Zabka::Simulation::~Simulation()
	{
	}

	VOID Zabka::Simulation::PreInitialize()
	{
		Logger::PrintDebugSeperator();
		Logger::PrintLog(L"Application Starting...\n");
		Logger::PrintLog(L"Game Name: %s\n", PerGameSettings::GameName());
		Logger::PrintLog(L"Boot Time: %s\n", Time::GetDateTimeString().c_str());
		Logger::PrintLog(L"Engine Mode: %s\n", Engine::EngineModeToString().c_str());
		Logger::PrintDebugSeperator();

		SplashScreen::Open();

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();

	}


	LRESULT Zabka::Simulation::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{

		switch (message)
		{

		}

		return CommonMessageHandler(hwnd, message, wParam, lParam);
	}
}