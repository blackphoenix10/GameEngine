#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Windows/Win32/WinEntry.h"

class BlankProject : public Zabka::Simulation {

	// BlankProject

public:

	// Constructor
	BlankProject() {};

	// Deconstructor
	~BlankProject() {};


public:

	VOID SetupPerGameSettings();

	// Called to Initialize the BlankProject
	VOID Initialize() {};

	// Game loop
	VOID Update() {};

};

ENTRYAPP(BlankProject)

VOID BlankProject::SetupPerGameSettings()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetMainIcon(IDI_MAINICON);
	PerGameSettings::SetSplashUrl(IDS_SPLASHURL);
}