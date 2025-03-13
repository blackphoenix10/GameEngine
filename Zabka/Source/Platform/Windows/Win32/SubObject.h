#pragma once

namespace Win32 {

	class SubObject {

	public:
		ZABKA_API SubObject(std::wstring className, std::wstring classTitle, HICON icon);
		ZABKA_API ~SubObject();

		virtual VOID ZABKA_API RegisterNewClass();
		virtual VOID ZABKA_API Initialize() = 0;

	protected:
		static			LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static			LRESULT				AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		virtual			LRESULT	ZABKA_API	CommonMessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
		virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
		// Accessor methods for derived classes


	
	private:
		std::wstring		m_Class = L"";
		std::wstring		m_Title = L"";
		HICON				m_hIcon = nullptr;
		HWND				m_Handle = nullptr;

	public:
		HWND ZABKA_API Handle() const { return m_Handle; }
		std::wstring ZABKA_API Class() { return m_Class; }
		std::wstring ZABKA_API Title() { return m_Title; }

	public:
		VOID	ZABKA_API Handle(HWND hwnd) { m_Handle = hwnd; }
	};
}