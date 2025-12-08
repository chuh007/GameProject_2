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


void GameScene::Init()
{
	Player* obj = new Player;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	// obj->SetScene(this);
	AddObject(obj, Layer::PLAYER);

	GET_SINGLE(PlayerManager)->SetPlayer(obj);
	//Spawn<Boss>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ITEM);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	GET_SINGLE(EnemySpawnManger)->Init();
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::Circle1, 100, Layer::ENEMYPROJECTILE);
	GET_SINGLE(PoolManager)->AddPool<PlayerProjectile>
		(PoolType::PlayerProj, 100, Layer::PROJECTILE);

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

	for (float i = 0; i < 9; i+= 3)
	{
		TripleShotEnemy* enemy = new TripleShotEnemy;

		enemy->SetPos({ 100, 100 });
		enemy->SetSize({ 100,100 });
		GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 10.f + i, enemy });
	}

}

void GameScene::Update()
{
	GET_SINGLE(EnemySpawnManger)->Update();
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
