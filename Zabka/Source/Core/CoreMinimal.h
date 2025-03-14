#pragma once


#include "CoreDefinitions.h"
#include "Engine/ZEngine.h"

#include "Common/Time.h"
#include "Common/Logger.h"
#include "PerGameSettings.h"
#include <string>

#ifdef WIN32

	#include "Platform/Windows/Win32/Win32Utils.h"
	#include "Platform/Windows/Win32/SubObject.h"
	#include "Platform/Windows/Win32/Window.h"
	#include "Platform/Windows/Win32/IApplication.h"
	#include "Platform/Windows/Win32/DirectX12Renderer.h"

#endif