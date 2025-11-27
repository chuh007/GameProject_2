#include "pch.h"
#include "TestEnemy.h"
#include "EnemyMovement.h"
#include "Health.h"

TestEnemy::TestEnemy()
	:pathData(nullptr)
{
	auto* col = GetComponent<Collider>();
	auto* movement = AddComponent<EnemyMovement>();
	col->SetSize(50.f);
	movement->SetSpeed(100.f);
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::SetPath(BezierPathData* path)
{
	pathData = path;
	auto* movement = GetComponent<EnemyMovement>();
	movement->SetPathData(path);
}
