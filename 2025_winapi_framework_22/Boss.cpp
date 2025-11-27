#include "pch.h"
#include "Boss.h"
#include "Health.h"
#include "Collider.h"
#include "BossMover.h"
#include "SceneManager.h"
Boss::Boss()
	: m_lifeCount(2)
{
	auto* col = AddComponent<Collider>();
	col->SetSize(50.f);
	auto* health = AddComponent<Health>();
	health->SetMaxHP(2000);
	health->SetCurrentHP(2000);
	auto* mover = AddComponent<BossMover>();
	mover->MoveTo({ GAME_WIDTH / 2, GAME_HEIGHT / 5 }, 3.f);
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
	Health* health = GetComponent<Health>();
	health->TakeDamage(_damage);
	cout << _damage << endl;
}

void Boss::HPZero()
{
	m_lifeCount--;
	if (m_lifeCount > 0)
	{
		Health* health = GetComponent<Health>();
		health->SetCurrentHP(health->GetMaxHP());
	}
	else
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}
