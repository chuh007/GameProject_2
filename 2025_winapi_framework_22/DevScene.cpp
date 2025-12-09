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
	GET_SINGLE(PlayerManager)->SetPlayer(player);
	Boss* boss = Spawn<Boss>(Layer::ENEMY, { GAME_WIDTH / 2, GAME_HEIGHT / 4 }, { 30.f, 70.f });
	boss->SetBackground(background);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::ENEMYPROJECTILE, Layer::PROJECTILEDELETER);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::EnemyProjectile, 500, Layer::ENEMYPROJECTILE);
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

	const int TEXT_START_X = GAME_WIDTH + 30;

	TextOut(_hdc, TEXT_START_X, 10, L"Render Test", 11);

	wstring lifeStr = std::format(L"LIFE : {}", life);
	TextOut(_hdc, TEXT_START_X, 50, lifeStr.c_str(), (int)lifeStr.length());

	wstring bombStr = std::format(L"BOMB : {}", bombCnt);
	TextOut(_hdc, TEXT_START_X, 100, bombStr.c_str(), (int)bombStr.length());

	wstring powerStr = std::format(L"POWER: {} / {}", power, 128);
	TextOut(_hdc, TEXT_START_X, 150, powerStr.c_str(), (int)powerStr.length());
}

void DevScene::Release() {
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

