#pragma once

#include "Platform/Windows/WIN32/IApplication.h"

class Application : public IApplication {

	// Application

public:

	// Constructor
	Application();

	// Deconstructor
	~Application();


public:

	VOID SetupPerGameSettings();

	// Called to Initialize the Application
	VOID Initialize();

	// Game loop
	VOID Update();

};