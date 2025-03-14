#pragma once

namespace Zabka {

	class Simulation : public Win32::IApplication, public Win32::Window {

	public:
		ZABKA_API Simulation();
		ZABKA_API ~Simulation();

		virtual VOID ZABKA_API PreInitialize() override;
		virtual VOID ZABKA_API Run();
		virtual VOID ZABKA_API Cleanup();
		virtual LRESULT ZABKA_API MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	private:
		DirectX12Renderer* renderer;
	};
}