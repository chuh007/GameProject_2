#include "pch.h"
#include "DevScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "EnemyProjectile.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "EnemySpawnManger.h"
#include "PoolManager.h"
#include "PlayerManager.h"
#include "BossHPBar.h"
#include "Projectile.h"
#include "Effect.h"
#include "Background.h"
#include "Texture.h"
void DevScene::Init()
{	
	//Object* obj = new Player;
	//obj->SetPos({ GAME_WIDTH / 2, 500 });
	//obj->SetSize({ 100.f, 100.f });
	//// obj->SetScene(this);
	//AddObject(obj, Layer::PLAYER);
	srand(time(nullptr));
	auto* background = Spawn<Background>(Layer::BACKGROUND, { GAME_WIDTH * 0.5f, GAME_HEIGHT * 0.5f }, { GAME_WIDTH, GAME_HEIGHT });
	auto* player = Spawn<Player>(Layer::PLAYER, { GAME_WIDTH / 2, 500 }, { 100.f, 100.f });
	player->GainPower(128);
	GET_SINGLE(PlayerManager)->SetPlayer(player);
	Boss* boss = Spawn<Boss>(Layer::ENEMY, { GAME_WIDTH / 2, GAME_HEIGHT / 4 }, { 30.f, 70.f });
	boss->SetBackground(background);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ITEM);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::ENEMYPROJECTILE, Layer::PROJECTILEDELETER);
	GET_SINGLE(ResourceManager)->Play(L"BossBGM");
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::EnemyProjectile, 1000, Layer::ENEMYPROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<PlayerProjectile>
		(PoolType::PlayerProj, 100, Layer::PROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<Effect>
		(PoolType::Effect, 10, Layer::ENEMYPROJECTILE);
	//GET_SINGLE(PoolManager)->AddPool

	boss->Start();

	auto* hpBar = Spawn<BossHPBar>(Layer::UI, { GAME_WIDTH / 2, 25 }, { GAME_WIDTH - 20, 50 });
	hpBar->SetBoss(boss);

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
}

void DevScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}

void DevScene::Render(HDC _hdc) {
	Scene::Render(_hdc);

	if (m_hdc != nullptr && m_hUIBitmap != nullptr)
	{
		BitBlt(_hdc,
			GAME_WIDTH, 0,
			m_uiWidth, m_uiHeight,
			m_hdc, 0, 0,
			SRCCOPY);
	}

	Player* player = GET_SINGLE(PlayerManager)->GetPlayer();
	if (!player) return;

	int life = player->GetLifeCount();
	int bombCnt = player->GetBombCount();
	int power = player->GetPowerLevel();

	SetTextColor(_hdc, RGB(0, 0, 0));
	SetBkMode(_hdc, TRANSPARENT);

	HFONT hFont = GET_SINGLE(ResourceManager)->GetFont(FontType::TITLE);
	HFONT hOldFont = nullptr;
	if (hFont != nullptr)
	{
		hOldFont = (HFONT)SelectObject(_hdc, hFont);
	}

	const int UI_START_X = GAME_WIDTH + 10;

	Texture* lTex = GET_SINGLE(ResourceManager)->GetTexture(L"LifeIcon");
	Texture* bTex = GET_SINGLE(ResourceManager)->GetTexture(L"BombIcon");

	LONG lifeWidth = lTex->GetWidth();
	LONG lifeHeight = lTex->GetHeight();
	LONG bombWidth = bTex->GetWidth();
	LONG bombHeight = bTex->GetHeight();

	const int ICON_GAP_LIFE = lifeWidth + 5;
	const int ICON_GAP_BOMB = bombWidth + 5;

	const int LIFE_TEXT_WIDTH_OFFSET = 80;
	const int BOMB_TEXT_WIDTH_OFFSET = 80;

	const int LIFE_START_Y = 50;

	wstring lifePrefix = L"LIFE : ";
	TextOut(_hdc, UI_START_X, LIFE_START_Y, lifePrefix.c_str(), (int)lifePrefix.length());

	for (int i = 0; i < life; ++i)
	{
		::TransparentBlt(
			_hdc,
			UI_START_X + LIFE_TEXT_WIDTH_OFFSET + (i * ICON_GAP_LIFE),
			LIFE_START_Y,
			lifeWidth, lifeHeight,
			lTex->GetTextureDC(),
			0, 0, lifeWidth, lifeHeight,
			RGB(255, 0, 255));
	}

	const int BOMB_START_Y = 100;

	wstring bombPrefix = L"BOMB : ";
	TextOut(_hdc, UI_START_X, BOMB_START_Y, bombPrefix.c_str(), (int)bombPrefix.length());

	for (int i = 0; i < bombCnt; ++i)
	{
		::TransparentBlt(
			_hdc,
			UI_START_X + BOMB_TEXT_WIDTH_OFFSET + (i * ICON_GAP_BOMB),
			BOMB_START_Y,
			bombWidth, bombHeight,
			bTex->GetTextureDC(),
			0, 0, bombWidth, bombHeight,
			RGB(255, 0, 255));
	}

	const int POWER_START_Y = 150;

	wstring powerStr = std::format(L"POWER: {} / {}", power, 128);
	TextOut(_hdc, UI_START_X, POWER_START_Y, powerStr.c_str(), (int)powerStr.length());

	if (hOldFont != nullptr)
	{
		SelectObject(_hdc, hOldFont);
	}
}

void DevScene::Release() {
	Scene::Release();
	if (m_hdc != nullptr) {
		SelectObject(m_hdc, m_hOldBitmap);
		DeleteDC(m_hdc);
		m_hdc = nullptr;
	}
	if (m_hUIBitmap != nullptr) {
		DeleteObject(m_hUIBitmap);
		m_hUIBitmap = nullptr;
	}

	Scene::Release();
}

