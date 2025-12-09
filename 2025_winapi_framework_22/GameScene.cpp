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
#include "ShotToPlayerEnemy.h"
#include "InputManager.h"
#include "ItemDropCompo.h"
#include "BombItem.h"
#include "PowerItem.h"
#include "Background.h"
#include "Effect.h"
#include "EnemyMovement.h"
#include "Health.h"
#include "Boss.h"

#pragma region 땜방용 매크로


#define CREATE_ENEMY(enemyType, posX, posY, sizeW, sizeH, collSize, maxHP, itemType, itemSizeW, itemSizeH) \
    Enemy* pEnemy = enemyType; \
    pEnemy->SetPos({ (float)posX, (float)posY }); \
    pEnemy->SetSize({ (float)sizeW, (float)sizeH }); \
\
    auto* coll = pEnemy->GetComponent<Collider>(); \
    if (coll) { \
        coll->SetSize((float)collSize); \
    } \
\
    auto* health = pEnemy->GetComponent<Health>(); \
    if (health) { \
        health->SetMaxHP((float)maxHP); \
        health->SetCurrentHP((float)maxHP); \
    } \
\
    Item* item = new itemType; \
    item->SetSize({ (float)itemSizeW, (float)itemSizeH }); \
\
    auto* itemDrop = pEnemy->AddComponent<ItemDropCompo>(); \
    if (itemDrop) { \
        itemDrop->SetItem(item); \
    }

#pragma endregion

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


	HBRUSH hUIBrush = CreateSolidBrush(RGB(230, 230, 230));
	RECT rect = { 0, 0, m_uiWidth, m_uiHeight };

	FillRect(m_hdc, &rect, hUIBrush);

	DeleteObject(hUIBrush);
	//여기서부터 적 세팅


	EnemySpawnManger* enemyManager = GET_SINGLE(EnemySpawnManger);
	enemyManager->SetSpawnScene(this);
	BezierPathData* wave1path = enemyManager->GetPath(L"Left-Right");
	BezierPathData* wave2path = enemyManager->GetPath(L"Right-Left");

	for(float i = 0; i < 3; i += 0.25f)
	{
		TestEnemy* testEnemy = new TestEnemy;
		CREATE_ENEMY(testEnemy, 0, 0, 75, 75, 75.f / 2, 20.f, PowerItem, 25.f, 25.f);

		auto* movecompo = testEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);
		movecompo->AddPathData(wave1path);
		movecompo->SetSpeed(300.f);

		enemyManager->AddEnemySpawnQueue({ i , testEnemy });
	}

	for(float i = 6; i < 9; i += 0.25f)
	{

		TestEnemy* testEnemy = new TestEnemy;
		CREATE_ENEMY(testEnemy, 800, 0, 75, 75, 75.f / 2, 20.f, PowerItem, 25.f, 25.f);

		auto* movecompo = testEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);
		movecompo->AddPathData(wave2path);
		movecompo->SetSpeed(300.f);

		enemyManager->AddEnemySpawnQueue({i , testEnemy });
	}

	BezierPathData* upandDown = enemyManager->GetPath(L"Down-Up");
	for (int i = 0; i < 4; ++i)
	{
		ShotToPlayerEnemy* fireEnemy = new ShotToPlayerEnemy;
		CREATE_ENEMY(fireEnemy, 100 + i * 200, 0, 75,75,75.f/2,50, PowerItem, 25.f,25.f);
		fireEnemy->SetFireTime(1.5f, 0.05f, 12, true);


		auto* movecompo = fireEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);
		movecompo->AddPathData(upandDown);
		movecompo->SetSpeed(150.0f);

		enemyManager->AddEnemySpawnQueue({ 12.f + i , fireEnemy });
	}
	BezierPathData* down = enemyManager->GetPath(L"Up");
	BezierPathData* zigzagR = enemyManager->GetPath(L"ZigzagR");
	BezierPathData* zigzagL = enemyManager->GetPath(L"ZigzagL");

	for (int i = 0; i < 10; ++i)
	{
		CircleMoveEnemy* fireEnemy = new CircleMoveEnemy;
		CREATE_ENEMY(fireEnemy, 100 + i * 200, 0, 75,75,75.f/2,50, PowerItem, 25.f,25.f);
		fireEnemy->SetShotCount(24);


		auto* movecompo = fireEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);

		for (int i = 0; i < 3; ++i)
		{
			movecompo->AddPathData(zigzagR);
			movecompo->AddPathData(zigzagL);
		}
		movecompo->SetSpeed(150.f);

		enemyManager->AddEnemySpawnQueue({ 20.f + i , fireEnemy });
	}
	for (float i = 25; i < 28; i += 0.25f)
	{
		TestEnemy* testEnemy = new TestEnemy;
		CREATE_ENEMY(testEnemy, 0, 0, 75, 75, 75.f / 2, 20.f, PowerItem, 25.f, 25.f);

		auto* movecompo = testEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);
		movecompo->AddPathData(wave1path);
		movecompo->SetSpeed(300.f);

		enemyManager->AddEnemySpawnQueue({ i , testEnemy });
	}
	for (float i = 28; i < 30; i += 0.25f)
	{

		TestEnemy* testEnemy = new TestEnemy;
		CREATE_ENEMY(testEnemy, 800, 0, 75, 75, 75.f / 2, 20.f, PowerItem, 25.f, 25.f);

		auto* movecompo = testEnemy->AddComponent<EnemyMovement>();
		movecompo->SetRepeatType(MoveRepeatType::Stop);
		movecompo->AddPathData(wave2path);
		movecompo->SetSpeed(300.f);

		enemyManager->AddEnemySpawnQueue({ i , testEnemy });
	}

	//여기까지 적 세팅
}

void GameScene::Update()
{
	Scene::Update();
	GET_SINGLE(EnemySpawnManger)->Update();
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
