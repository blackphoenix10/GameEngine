#include "Zabka.h"
#include <wchar.h> // Add this include for wcscpy_s

PerGameSettings* PerGameSettings::inst;

PerGameSettings::PerGameSettings()
{
    inst = this;
    wcscpy_s(inst->m_GameName, sizeof(inst->m_GameName)/sizeof(wchar_t), L"undefined");
    wcscpy_s(inst->m_ShortName, sizeof(inst->m_ShortName)/sizeof(wchar_t), L"undefined");
    wcscpy_s(inst->m_BootTime, sizeof(inst->m_BootTime)/sizeof(wchar_t), Time::GetDateTimeString(TRUE).c_str());
    wcscpy_s(inst->m_SplashUrl, sizeof(inst->m_SplashUrl)/sizeof(wchar_t), L"..\\Content\\Images\\frog_splash.bmp");
}

PerGameSettings::~PerGameSettings()
{
}