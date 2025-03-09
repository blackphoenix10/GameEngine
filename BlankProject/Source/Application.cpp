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

VOID Application::SetupPerGameSettings()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
}

VOID Application::Initialize()
{

}

VOID Application::Update()
{

}
