#include "pch.h"
#include "Boss.h"
#include "Health.h"
Boss::Boss()
{
	AddComponent<Collider>();
	auto* health = AddComponent<Health>();
	health->SetMaxHP(100);
	health->SetCurrentHP(100);
}

Boss::~Boss()
{
}

void Boss::Update()
{

}

void Boss::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);

	ComponentRender(_hdc);
}

void Boss::EnterCollision(Collider* _other)
{
}

void Boss::TakeDamage(int _damage)
{
}

void Boss::HPZero()
{
}
