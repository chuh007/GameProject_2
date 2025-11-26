#include "pch.h"
#include "TestEnemy.h"
#include "EnemyMovement.h"
#include "Health.h"

TestEnemy::TestEnemy()
{
	auto* col = GetComponent<Collider>();
	auto* movement = AddComponent<EnemyMovement>();
	col->SetSize(50.f);
	vector<Vec2> points{ {0,0},{300,300}, {300,0}, {600,300}, {600, 800} };
	movement->SetBezierPoints(points);
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
}

void TestEnemy::TakeDamage(int _damage)
{
}

void TestEnemy::HPZero()
{
}
