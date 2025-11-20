#include "pch.h"
#include "DevScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Floor.h"
void DevScene::Init()
{	
	Object* obj = new Player;
	obj->SetPos({ WINDOW_WIDTH / 2, 300 });
	obj->SetSize({ 100.f, 100.f });
	// obj->SetScene(this);
	AddObject(obj, Layer::PLAYER);

	Spawn<Floor>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 600}, { 100.f,100.f });
	Spawn<Enemy>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void DevScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
}
