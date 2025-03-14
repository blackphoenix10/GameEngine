#pragma once

#define ENTRYAPP(x) Win32::IApplication* EntryApplication() {return new x; }

namespace Win32 {

	class ZABKA_API IApplication {

	public:
		// Constructor
		IApplication();

		// Destructor
		virtual ~IApplication() {};

	public:
		// Called to Setup Per Game Settings
		virtual VOID SetupPerGameSettings() = 0;

		// Pre-initialization
		virtual VOID PreInitialize() = 0;

		// Called to Initialize the Application
		virtual VOID Initialize() = 0;

		// Game loop
		virtual VOID Update() = 0;

		// Run the application
		virtual VOID Run() = 0;

		// Cleanup resources
		virtual VOID Cleanup() = 0;
	};

	IApplication* EntryApplication();
}