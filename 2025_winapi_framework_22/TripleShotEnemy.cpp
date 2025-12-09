#include "pch.h"
#include "TripleShotEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

TripleShotEnemy::TripleShotEnemy()
	: pathData(nullptr)
{
	fireTime = 0;
}

TripleShotEnemy::~TripleShotEnemy()
{
}

void TripleShotEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 0.5f)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto* projectile = PoolManager::GetInst()->
				Pop<EnemyProjectile>(PoolType::EnemyProjectile);
			projectile->SetSize({ 10.f, 10.f });
			projectile->SetColliderSize(7.5f);
			projectile->SetPos(GetPos());
			projectile->SetDir(-90.f + (i-1) * 30);
			projectile->SetSpeed(500.f);
		}
		fireTime = 0;
	}
}
