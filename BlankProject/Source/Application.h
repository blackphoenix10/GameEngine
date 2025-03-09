#pragma once

#include "Engine/Simulation.h"

class Application : public Zabka::Simulation {

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