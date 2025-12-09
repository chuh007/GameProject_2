#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "CollisionManager.h"
#include "PlayerManager.h"
#include "TestEnemy.h"
#include "ResourceManager.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "CircleMoveEnemy.h"
#include "TripleShotEnemy.h"
#include "InputManager.h"
#include "ItemDropCompo.h"
#include "BombItem.h"
#include "Background.h"
#include "Effect.h"
#include "Boss.h"

void GameScene::Init()
{
	auto* player = Spawn<Player>(Layer::PLAYER, { GAME_WIDTH / 2, 500 }, { 100.f, 100.f });
	// obj->SetScene(this);
	GET_SINGLE(PlayerManager)->SetPlayer(player);

	Spawn<Background>(Layer::BACKGROUND, { GAME_WIDTH * 0.5f, GAME_HEIGHT * 0.5f }, { GAME_WIDTH, GAME_HEIGHT });
	//Spawn<Boss>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
	
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMYPROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::ENEMYPROJECTILE, Layer::PROJECTILEDELETER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ITEM);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	GET_SINGLE(EnemySpawnManger)->Init();
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::EnemyProjectile, 100, Layer::ENEMYPROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::IceProj, 50, Layer::ENEMYPROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<PlayerProjectile>
		(PoolType::PlayerProj, 100, Layer::PROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<Effect>
		(PoolType::Effect, 10, Layer::ENEMYPROJECTILE);

	m_uiWidth = WINDOW_WIDTH - GAME_WIDTH;
	m_uiHeight = WINDOW_HEIGHT;

	HWND hWnd = GetActiveWindow();
	HDC hScreenDC = GetDC(hWnd);
	m_hdc = CreateCompatibleDC(hScreenDC);

	m_hUIBitmap = CreateCompatibleBitmap(hScreenDC, m_uiWidth, m_uiHeight);
	ReleaseDC(hWnd, hScreenDC);

	m_hOldBitmap = (HBITMAP)SelectObject(m_hdc, m_hUIBitmap);

	//여기서부터 적 세팅
	TestEnemy* testEnemy = new TestEnemy;
	CircleMoveEnemy* circleEnemy = new CircleMoveEnemy;
	TripleShotEnemy* tripleshot = new TripleShotEnemy;

	testEnemy->SetPos({ 100, 100 });
	testEnemy->SetSize({ 75,75 });
	circleEnemy->SetPos({ 100, 100 });
	circleEnemy->SetSize({ 50,50 });
	tripleshot->SetPos({ 100,100 });
	tripleshot->SetSize({ 100,100 });

	auto* itemCompo = tripleshot->AddComponent<ItemDropCompo>();
	Item* bomb = new BombItem;
	bomb->SetSize({ 50.f,50.f });
	itemCompo->SetItem(bomb);
	GET_SINGLE(EnemySpawnManger)->SetSpawnScene(this);
	GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 3.f, testEnemy });
	GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 6.f, circleEnemy });
	GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 9.f, tripleshot });
	GET_SINGLE(EnemySpawnManger)->AddBossSpawn(20.f);

	for (float i = 0; i < 9; i+= 3)
	{
		TripleShotEnemy* enemy = new TripleShotEnemy;

		enemy->SetPos({ 100, 100 });
		enemy->SetSize({ 100,100 });
		GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 12.f + i, enemy });
	}

	//여기까지 적 세팅

	HBRUSH hUIBrush = CreateSolidBrush(RGB(230, 230, 230));
	RECT rect = { 0, 0, m_uiWidth, m_uiHeight };

	FillRect(m_hdc, &rect, hUIBrush);

	DeleteObject(hUIBrush);
}

void GameScene::Update()
{
	GET_SINGLE(EnemySpawnManger)->Update();
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}

void GameScene::Render(HDC _hdc) {
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

void GameScene::Release()
{
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
}
