#pragma once

#ifdef WIN32
#include <Windows.h>

#endif

#ifdef BUILD_DLL
	#define ZABKA_API __declspec(dllexport)
#else
	#define ZABKA_API __declspec(dllimport)
#endif