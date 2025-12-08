#include "pch.h"
#include "ButtonSelector.h"
#include "InputManager.h"
#include "Button.h"
ButtonSelector::ButtonSelector()
{
	btns = vector<Button*>(0);
	curSelectedIdx = 0;
	m_lastSelectTime = 0;
	m_isActive = false;
}
ButtonSelector::~ButtonSelector()
{
	btns.erase(btns.begin(), btns.end());
}
void ButtonSelector::Render(HDC _hdc)
{
	if (m_isActive)
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();
		RECT_RENDER(_hdc, pos.x, pos.y
			, size.x, size.y);
	}
}

void ButtonSelector::Update()
{
	m_lastSelectTime += fDT;
	if (GET_KEYDOWN(KEY_TYPE::S) || GET_KEYDOWN(KEY_TYPE::DOWN))
	{
		curSelectedIdx = (curSelectedIdx + 1) % btns.size();
		MoveToCurrentSelect();
		m_isActive = true;
		m_lastSelectTime = 0;
	}
	else if (GET_KEYDOWN(KEY_TYPE::W) || GET_KEYDOWN(KEY_TYPE::UP))
	{
		curSelectedIdx = (curSelectedIdx - 1) < 0 ? btns.size()-1 : curSelectedIdx - 1;
		MoveToCurrentSelect();
		m_isActive = true;
		m_lastSelectTime = 0;
	}
	else if (GET_KEYDOWN(KEY_TYPE::ENTER) || GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		cout << curSelectedIdx << endl;
		btns[curSelectedIdx]->OnClick();
	}

	if (m_lastSelectTime >= 3.f)
	{
		m_isActive = false;
	}
}

void ButtonSelector::AssignButton(Button* button)
{
	btns.push_back(button);
}

void ButtonSelector::MoveToCurrentSelect()
{
	float y = btns[curSelectedIdx]->GetPos().y;
	float x = btns[curSelectedIdx]->GetPos().x;
	x -= btns[curSelectedIdx]->GetSize().x / 2;
	x -= 50.f;
	SetPos({x,y});
}
