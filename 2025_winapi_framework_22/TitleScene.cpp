#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Button.h"
#include "StartButton.h"
#include "ButtonSelector.h"
#include "ExitButton.h"
#include "TitleBackground.h"
#include "ResourceManager.h";
#include "Texture.h"

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

	Texture* bgTex = GET_SINGLE(ResourceManager)->GetTexture(L"UIBackground");

	if (bgTex != nullptr)
	{
		LONG bgWidth = bgTex->GetWidth();
		LONG bgHeight = bgTex->GetHeight();

		::TransparentBlt(
			m_hdc,
			0, 0, m_uiWidth, m_uiHeight,
			bgTex->GetTextureDC(),
			0, 0, bgWidth, bgHeight,
			RGB(255, 0, 255));
	}
	else
	{
		HBRUSH hUIBrush = CreateSolidBrush(RGB(230, 230, 230));
		RECT rect = { 0, 0, m_uiWidth, m_uiHeight };
		FillRect(m_hdc, &rect, hUIBrush);
		DeleteObject(hUIBrush);
	}

	StartButton* button = new StartButton;
	button->SetSize({ 200.f, 50.f });
	button->SetPos({ GAME_WIDTH - button->GetSize().x / 2 - 25, btnpositionY});
	button->SetText(L"Start");
	button->SetSceneName(L"Game");

	btnpositionY += 60.0f;

	StartButton* enterBoss = new StartButton;
	enterBoss->SetSize({ 200.f, 50.f });
	enterBoss->SetPos({ GAME_WIDTH - button->GetSize().x / 2 - 25, btnpositionY });
	enterBoss->SetText(L"ToBoss");
	enterBoss->SetSceneName(L"DevScene");

	btnpositionY += 60.0f;

	Button* exit = new ExitButton;
	exit->SetSize({ 200.f, 50.f });
	exit->SetPos({ GAME_WIDTH - button->GetSize().x / 2 - 25, btnpositionY });
	exit->SetText(L"Exit");
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	GET_SINGLE(ResourceManager)->Play(L"TitleBGM");

	


	AddObject(button, Layer::UI);
	AddObject(exit, Layer::UI);
	AddObject(enterBoss, Layer::UI);
	selector->AssignButton(button);
	selector->AssignButton(enterBoss);
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

	Texture* gTex = GET_SINGLE(ResourceManager)->GetTexture(L"TitleText");

	if (gTex != nullptr)
	{
		LONG logoWidth = gTex->GetWidth();
		LONG logoHeight = gTex->GetHeight();
		
		const int RENDER_X = 50;
		const int RENDER_Y = 10;
		const int RENDER_WIDTH = 143;
		const int RENDER_HEIGHT = 670;

		::TransparentBlt(
			_hdc,
			RENDER_X,
			RENDER_Y,
			RENDER_WIDTH, RENDER_HEIGHT,
			gTex->GetTextureDC(),
			0, 0, logoWidth, logoHeight,
			RGB(255, 0, 255));
	}

	SetTextColor(_hdc, RGB(255,255,255));
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
