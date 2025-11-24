#include "pch.h"
#include "DevScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Boss.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "EnemySpawnManger.h"
void DevScene::Init()
{	
	Object* obj = new Player;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	// obj->SetScene(this);
	AddObject(obj, Layer::PLAYER);

	Spawn<Boss>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	Enemy* enemy = new Enemy;
	enemy->SetSize({ 100.0f, 100.0f });
	enemy->SetPos({ 200.0f, 0.0f });
	GET_SINGLE(EnemySpawnManger)->SetSpawnScene(this);
	GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 1.0f, enemy});
	GET_SINGLE(EnemySpawnManger)->Init();
	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void DevScene::Update()
{
	Scene::Update();
	GET_SINGLE(EnemySpawnManger)->Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
