#include "pch.h"
#include "TestEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "Health.h"

TestEnemy::TestEnemy()
	:pathData(nullptr)
{
	auto* col = GetComponent<Collider>();
	auto* movement = AddComponent<EnemyMovement>();
	col->SetSize(50.f);
	movement->SetSpeed(100.f);
	movement->SetPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Default"));
}

TestEnemy::~TestEnemy()
{
}
