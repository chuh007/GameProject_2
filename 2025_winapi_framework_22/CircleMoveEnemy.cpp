#include "pch.h"

#include <functional>
#include "CircleMoveEnemy.h"
#include "EnemyMovement.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

CircleMoveEnemy::CircleMoveEnemy()
	: pathData(nullptr)
{
	auto* col = GetComponent<Collider>();
	auto* movement = AddComponent<EnemyMovement>();
	col->SetSize(25.f);
	movement->SetSpeed(200.0f);
	movement->SetDefaultPos({ 300,300 });
	movement->AddPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Up"));
	movement->AddPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Right"));
	movement->AddPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Down"));
	movement->AddPathData(GET_SINGLE(EnemySpawnManger)->GetPath(L"Left"));
	movement->SetRepeatType(MoveRepeatType::Repeat);
	fireTime = 0;
}

CircleMoveEnemy::~CircleMoveEnemy()
{
}

void CircleMoveEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 1.f)
	{
		for (int i = 0; i < 6; ++i)
		{
			auto* projectile = PoolManager::GetInst()->
				Pop<EnemyProjectile>(PoolType::Circle1);
			projectile->SetSize({ 10.f, 10.f });
			projectile->SetColliderSize(7.5f);
			projectile->SetPos(GetPos());
			projectile->SetDir(-90.f + i * 60.f);
			projectile->SetSpeed(500.f);

			fireTime = 0;
		}
	}
}
