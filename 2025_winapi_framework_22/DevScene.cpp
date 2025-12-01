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
void DevScene::Init()
{	
	//Object* obj = new Player;
	//obj->SetPos({ GAME_WIDTH / 2, 500 });
	//obj->SetSize({ 100.f, 100.f });
	//// obj->SetScene(this);
	//AddObject(obj, Layer::PLAYER);
	auto* player = Spawn<Player>(Layer::PLAYER, { GAME_WIDTH / 2, 500 }, { 100.f, 100.f });
	GET_SINGLE(PlayerManager)->SetPlayer(player);
	Boss* boss = Spawn<Boss>(Layer::ENEMY, { GAME_WIDTH / 2, GAME_HEIGHT / 4 }, { 50.f,75.f });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
	GET_SINGLE(PoolManager)->AddPool<EnemyProjectile>
		(PoolType::Circle1, 100, Layer::ENEMYPROJECTILE);

	auto* hpBar = Spawn<BossHPBar>(Layer::UI, { GAME_WIDTH / 2, 25 }, { GAME_WIDTH - 20, 50 });
	hpBar->SetBoss(boss);
}

void DevScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
