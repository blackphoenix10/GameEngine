#pragma once

#define ENTRYAPP(x) Win32::IApplication* EntryApplication() {return new x; }

namespace Win32 {

	class ZABKA_API IApplication {

		// Application

	public:

		// Constructor
		IApplication();

		// Deconstructor
		virtual ~IApplication() {};


	public:

		// Called to Setup Per Game Settings
		virtual VOID SetupPerGameSettings() = 0;

		virtual VOID PreInitialize() = 0;

		// Called to Initialize the Application
		virtual VOID Initialize() = 0;

		// Game loop
		virtual VOID Update() = 0;

	};

	IApplication* EntryApplication();

}