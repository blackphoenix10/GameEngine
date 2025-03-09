#pragma once

#include "Platform/Windows/Win32/IApplication.h"

namespace Zabka {

	class ZABKA_API Simulation : public Win32::IApplication {

	public:
		Simulation();
		~Simulation();

		virtual VOID PreInitialize() override;
	};
}