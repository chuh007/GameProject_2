#include "pch.h"
#include "GameOverScene.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "ButtonSelector.h"

void GameOverScene::Init()
{
	m_uiWidth = WINDOW_WIDTH - GAME_WIDTH;
	m_uiHeight = WINDOW_HEIGHT;

	HWND hWnd = GetActiveWindow();
	HDC hScreenDC = GetDC(hWnd);
	m_hdc = CreateCompatibleDC(hScreenDC);

	m_hUIBitmap = CreateCompatibleBitmap(hScreenDC, m_uiWidth, m_uiHeight);
	ReleaseDC(hWnd, hScreenDC);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hdc, m_hUIBitmap);

	HBRUSH hUIBrush = CreateSolidBrush(RGB(230, 230, 230));
	RECT rect = { 0, 0, m_uiWidth, m_uiHeight };

	FillRect(m_hdc, &rect, hUIBrush);

	DeleteObject(hUIBrush);
	
	ButtonSelector* selector = new ButtonSelector;
	selector->SetSize({ 50.f,50.f });
	AddObject(selector, Layer::UI);

	float btnpositionY = GAME_HEIGHT * 2 / 3;
	StartButton* button = new StartButton;
	button->SetSize({ 200.f, 50.f });
	button->SetPos({ GAME_WIDTH/2.0f , btnpositionY });
	button->SetText(L"Title");
	button->SetSceneName(L"Title");

	btnpositionY += 60.0f;

	Button* exit = new ExitButton;
	exit->SetSize({ 200.f, 50.f });
	exit->SetPos({ GAME_WIDTH / 2.0f, btnpositionY });
	exit->SetText(L"Exit");

	AddObject(button, Layer::UI);
	AddObject(exit, Layer::UI);
	selector->AssignButton(button);
	selector->AssignButton(exit);
}

void GameOverScene::Update()
{
	Scene::Update();
}

void GameOverScene::Release()
{
	Scene::Release();
}

void GameOverScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	if (m_hdc != nullptr && m_hUIBitmap != nullptr)
	{
		BitBlt(_hdc,
			GAME_WIDTH, 0,
			m_uiWidth, m_uiHeight,
			m_hdc, 0, 0,
			SRCCOPY);
	}
}
