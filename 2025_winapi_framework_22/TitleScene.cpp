#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Button.h"
#include "StartButton.h"
#include "ButtonSelector.h"
#include "ExitButton.h"
#include "TitleBackground.h"
#include "ResourceManager.h";

TitleScene::~TitleScene()
{
	Scene::~Scene();
}

void TitleScene::Init()
{

	ButtonSelector* selector = new ButtonSelector;
	selector->SetSize({ 50.f,50.f });
	AddObject(selector, Layer::UI);
	float btnpositionY = GAME_HEIGHT *2/3;

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

	float buttonX = GAME_WIDTH - 125.f;

	StartButton* button = Spawn<StartButton>(Layer::UI, { buttonX, btnpositionY }, { 200.f, 50.f });
	button->SetText(L"Start");
	button->SetSceneName(L"Game");

	btnpositionY += 60.0f;

	StartButton* enterBoss = Spawn<StartButton>(Layer::UI, { buttonX, btnpositionY }, { 200.f, 50.f });
	enterBoss->SetText(L"ToBoss");
	enterBoss->SetSceneName(L"DevScene");

	btnpositionY += 60.0f;

	StartButton* setting = Spawn<StartButton>(Layer::UI, { buttonX, btnpositionY }, { 200.f, 50.f });

	setting->SetText(L"Setting");
	setting->SetSceneName(L"Setting");

	btnpositionY += 60.0f;

	Button* exit = Spawn<ExitButton>(Layer::UI, { buttonX, btnpositionY }, { 200.f, 50.f });
	exit->SetText(L"Exit");
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	GET_SINGLE(ResourceManager)->Play(L"TitleBGM");

	selector->AssignButton(button);
	selector->AssignButton(enterBoss);
	selector->AssignButton(setting);
	selector->AssignButton(exit);

	Object* bg = new TitleBackground;
	bg->SetPos({ GAME_WIDTH/2, GAME_HEIGHT/2 });
	bg->SetSize({GAME_WIDTH, GAME_HEIGHT});
	AddObject(bg, Layer::BACKGROUND);
}

void TitleScene::Render(HDC _hdc) {
	Scene::Render(_hdc);

	if (m_hdc != nullptr && m_hUIBitmap != nullptr)
	{
		BitBlt(_hdc,
			GAME_WIDTH, 0,
			m_uiWidth, m_uiHeight,
			m_hdc, 0, 0,
			SRCCOPY);
	}

	SetTextColor(_hdc, RGB(0,0,0));
	SetBkMode(_hdc, TRANSPARENT);

	const int TEXT_START_X = GAME_WIDTH + 30;

	TextOut(_hdc, TEXT_START_X, 10, L"조작법 :", 5);
	TextOut(_hdc, TEXT_START_X, 50, L"W, A, S, D : 이동", 15);
	TextOut(_hdc, TEXT_START_X, 75, L"Q : 봄", 5);
	TextOut(_hdc, TEXT_START_X, 100, L"Space, 위쪽 화살표 : 발사", 18);
	TextOut(_hdc, TEXT_START_X, 125, L"Shiift : 느린 이동", 14);
}

void TitleScene::Release()
{
	Scene::Release();
}
