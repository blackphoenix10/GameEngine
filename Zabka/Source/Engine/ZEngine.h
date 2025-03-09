#pragma once 

class ZABKA_API ZEngine;
namespace Engine {

	enum  EngineMode : INT {
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern ZEngine g_ZabkaEngine;

	VOID ZABKA_API SetMode(EngineMode mode);
	EngineMode ZABKA_API GetMode();

	std::wstring ZABKA_API EngineModeToString();

}

using namespace Engine;
class ZABKA_API ZEngine {

public:
	ZEngine();
	~ZEngine();

private:
	EngineMode m_EngineMode;

public:
	EngineMode GetEngineMode() const;
	VOID SetEngineMode(EngineMode mode);

};