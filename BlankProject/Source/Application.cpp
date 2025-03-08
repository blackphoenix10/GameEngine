#include "pch.h"
#include "Application.h"
#include "Platform/Windows/WIN32/WinEntry.h"


ENTRYAPP(Application)

Application::Application()
{
}

Application::~Application()
{
}

VOID Application::Initialize()
{
	MessageBox(0, L"I have loaded", 0, 0);

}

VOID Application::Update()
{
	return VOID();
}
