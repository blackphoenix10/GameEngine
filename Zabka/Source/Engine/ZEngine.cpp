#include "Zabka.h"

namespace Engine {

	ZEngine g_ZabkaEngine;

	VOID SetMode(EngineMode mode){ g_ZabkaEngine.SetEngineMode(mode); }

	EngineMode GetMode(){ return g_ZabkaEngine.GetEngineMode(); }

	std::wstring ZABKA_API EngineModeToString()
	{
		switch (Engine::GetMode())
		{
		case EngineMode::DEBUG:     return L"Debug";
		case EngineMode::RELEASE:   return L"Release";
		case EngineMode::SERVER:    return L"Server";
		case EngineMode::EDITOR:    return L"Editor";
		default:                    return L"None";
		}
	}
}


ZEngine::ZEngine()
{

#ifdef _DEBUG
	m_EngineMode = EngineMode::DEBUG;
#else
	m_EngineMode = EngineMode::RELEASE;
#endif
}

ZEngine::~ZEngine(){}

EngineMode ZEngine::GetEngineMode() const{return m_EngineMode;}

VOID ZEngine::SetEngineMode(EngineMode mode) {m_EngineMode = mode;}