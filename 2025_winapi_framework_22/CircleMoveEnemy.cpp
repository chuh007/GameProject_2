#include "pch.h"

#include <functional>
#include "CircleMoveEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

CircleMoveEnemy::CircleMoveEnemy()
{
	fireCount = 0;
	fireTime = 0;
}

CircleMoveEnemy::~CircleMoveEnemy()
{
}

void CircleMoveEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 1.5f)
	{
		float dir = 360 / fireCount;
		for (int i = 0; i <= fireCount; ++i)
		{
			auto* projectile = PoolManager::GetInst()->
				Pop<EnemyProjectile>(PoolType::EnemyProjectile);
			projectile->SetSize({ 10.f, 10.f });
			projectile->SetColliderSize(7.5f);
			projectile->SetPos(GetPos());
			projectile->SetDir(-90.f + i * dir);
			projectile->SetSpeed(300.f);

			fireTime = 0;
		}
	}
}

void CircleMoveEnemy::SetShotCount(int count)
{
	fireCount = count;
}
