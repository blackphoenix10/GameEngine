#pragma once
#include "SubObject.h"

namespace Win32 {
	
	class ZABKA_API Window : public Win32::SubObject {

	public:
		Window(std::wstring title, HICON icon, WindowType type = RESIZABLE);
		~Window();

		virtual VOID Initialize() override;

	protected:


		SIZE		m_Size;
		WindowType	m_Type;

	public:
		SIZE		Size() { return m_Size; }
		
	public:
		VOID		Size(SIZE size) { m_Size = size; }
		VOID		Size(INT cx, INT cy) { m_Size.cx = cx; m_Size.cy = cy; }
	};
}