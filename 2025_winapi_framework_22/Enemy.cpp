#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "Health.h"
Enemy::Enemy()
{
	AddComponent<Collider>();
	auto* health = AddComponent<Health>();
	health->SetMaxHP(100);
	health->SetCurrentHP(100);
}
Enemy::~Enemy()
{
}
void Enemy::Update()
{
}

void Enemy::Render(HDC _hdc)
{
	
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);

	ComponentRender(_hdc);
}

void Enemy::EnterCollision(Collider* _other)
{
	cout << "Enter" << endl;
}

void Enemy::StayCollision(Collider* _other)
{
	cout << "Stay" << endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	cout << "Exit" << endl;
}

void Enemy::TakeDamage(int _damage)
{
	Health* health = GetComponent<Health>();
	health->TakeDamage(_damage);
	cout << _damage << endl;
}

void Enemy::HPZero()
{
	cout << "dho";
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}
