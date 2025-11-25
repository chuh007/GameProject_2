#include "pch.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	AddComponent<Collider>();
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
}

void TestEnemy::Render(HDC _hDC)
{
}

void TestEnemy::EnterCollision(Collider* _other)
{
}

void TestEnemy::StayCollision(Collider* _other)
{
}

void TestEnemy::ExitCollision(Collider* _other)
{
}

void TestEnemy::TakeDamage(int _damage)
{
}

void TestEnemy::HPZero()
{
}
