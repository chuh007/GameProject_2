#include "pch.h"
#include "BakBakDevScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Boss.h"
#include "TestEnemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "EnemySpawnManger.h"
#include "MathHelper.h"
void BakBakDevScene::Init()
{
	Object* obj = new Player;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	// obj->SetScene(this);
	AddObject(obj, Layer::PLAYER);

	Spawn<Boss>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	BezierPathData* pathData = new BezierPathData;
	pathData->CalculateArcLengthMap({ {0,0},{300,300},{600,600},{500,800} });
	
	GET_SINGLE(EnemySpawnManger)->Init();
	TestEnemy* testEnemy = new TestEnemy;
	testEnemy->SetPos({ 100, 100 });
	testEnemy->SetSize({ 100,100 });
	GET_SINGLE(EnemySpawnManger)->SetSpawnScene(this);
	GET_SINGLE(EnemySpawnManger)->AddEnemySpawnQueue({ 3.f, testEnemy });
}

void BakBakDevScene::Update()
{
	GET_SINGLE(EnemySpawnManger)->Update();
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
