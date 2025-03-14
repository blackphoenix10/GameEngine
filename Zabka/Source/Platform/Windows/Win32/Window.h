#pragma once
#include "SubObject.h"

namespace Win32 {
	
	class Window : public Win32::SubObject {

	public:
		ZABKA_API Window(std::wstring title, HICON icon, WindowType type = RESIZABLE);
		~Window();

		virtual VOID ZABKA_API Initialize() override;

	protected:


		SIZE		m_Size;
		WindowType	m_Type;

	public:
		SIZE		ZABKA_API Size() const { return m_Size; }
		
	public:
		VOID		ZABKA_API Size(SIZE size) { m_Size = size; }
		VOID		ZABKA_API Size(INT cx, INT cy) { m_Size.cx = cx; m_Size.cy = cy; }
	};
}