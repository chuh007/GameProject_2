#include "pch.h"
#include <functional>
#include "TestEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

TestEnemy::TestEnemy()
{
	fireTime = 0;
}

TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 0.75f)
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
