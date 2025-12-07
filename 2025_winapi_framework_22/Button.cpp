#include "pch.h"
#include "Button.h"
#include "InputManager.h"

void Button::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);

	GDISelector(_hdc, FontType::TITLE);
	TextOut(_hdc, pos.x - size.x/2 + 15, pos.y - size.y/2 + 15 , m_text.c_str(), m_text.size());
}

void Button::Update()
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT r = RECT_MAKE(pos.x, pos.y, size.x, size.y);
	Vec2 mousePos = GET_MOUSEPOS;

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON)
		&& mousePos.x >= r.left 
		&& mousePos.x <= r.right 
		&& mousePos.y <= r.bottom 
		&& mousePos.y >= r.top)
	{
		OnClick();
	}
}

void Button::OnClick()
{
	cout << "Clicked" << endl;
}

void Button::SetText(const wstring& str)
{
	m_text = str;
}
