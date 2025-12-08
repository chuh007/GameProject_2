#include "pch.h"
#include <functional>
#include "TestEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

TestEnemy::TestEnemy()
	:pathData(nullptr)
{
	auto* col = GetComponent<Collider>();
	auto* movement = AddComponent<EnemyMovement>();
	col->SetSize(75.f/2);
	movement->SetDefaultPos({ 100,100 });
	movement->SetSpeed(200.0f);
	movement->AddPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Default"));
	fireTime = 0;
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 1.f)
	{
		auto* projectile = PoolManager::GetInst()->
			Pop<EnemyProjectile>(PoolType::EnemyProjectile);
		projectile->SetSize({ 10.f, 10.f });
		projectile->SetColliderSize(7.5f);
		projectile->SetPos(GetPos());
		projectile->SetDir(-90.f);
		projectile->SetSpeed(500.f);

		fireTime = 0;
	}
}
