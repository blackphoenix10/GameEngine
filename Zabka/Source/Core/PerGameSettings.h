#pragma once

class ZABKA_API PerGameSettings {

private:
	// Singleton reference to static class
	static PerGameSettings* inst;

	static PerGameSettings* Instance() { return inst; }

public:
	// Constructor with Singleton assignment
	PerGameSettings();
	~PerGameSettings();

private:

	WCHAR m_GameName[MAX_NAME_STRING] = L"";
	WCHAR m_ShortName[MAX_NAME_STRING] = L"";
	HICON m_MainIcon = HICON();
	WCHAR m_BootTime[MAX_NAME_STRING] = L"";
	WCHAR m_SplashUrl[MAX_NAME_STRING] = L"";

public:

	static WCHAR* GameName() { return inst->m_GameName; }
	static VOID SetGameName(UINT id) { LoadString(HInstance(), id, inst->m_GameName, MAX_NAME_STRING); }

	static WCHAR* ShortName() { return inst->m_ShortName; }
	static VOID SetShortName(UINT id) { LoadString(HInstance(), id, inst->m_ShortName, MAX_NAME_STRING); }

	static HICON MainIcon() { return inst->m_MainIcon; }
	static VOID SetMainIcon(UINT id) { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static WCHAR* BootTime() { return inst->m_BootTime; }

	static WCHAR* SplashUrl() { return inst->m_SplashUrl; }
	static VOID SetSplashUrl(UINT id) { LoadString(HInstance(), id, inst->m_SplashUrl, MAX_NAME_STRING); }

};