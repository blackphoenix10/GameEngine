#pragma once


#ifdef WIN32
#include <Windows.h>

#endif

#ifdef BUILD_DLL
	#define ZABKA_API __declspec(dllexport)
#else
	#define ZABKA_API __declspec(dllimport)
#endif

#define MAX_NAME_STRING 256
#define	HInstance() GetModuleHandle(NULL)

#include "Core/PerGameSettings.h"
#include "Common/Time.h"
#include "Common/Logger.h"
