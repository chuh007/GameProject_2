#include "pch.h"
#include "TripleShotEnemy.h"
#include "EnemyMovement.h"
#include "ResourceManager.h"
#include "EnemySpawnManger.h"
#include "EnemyProjectile.h"
#include "Health.h"

TripleShotEnemy::TripleShotEnemy()
	: pathData(nullptr)
{
	m_pTextrue = GET_SINGLE(ResourceManager)->GetTexture(L"GreenBullet1");
	fireTime = 0;
}

TripleShotEnemy::~TripleShotEnemy()
{
}

void TripleShotEnemy::Update()
{
	fireTime += fDT;
	if (fireTime >= 0.75f)
	{
		for (int i = 0; i < 3; ++i)
		{
			auto* projectile = PoolManager::GetInst()->
				Pop<EnemyProjectile>(PoolType::EnemyProjectile);
			projectile->SetSize({ 20.f, 20.f });
			projectile->SetColliderSize(7.5f);
			projectile->SetPos(GetPos());
			projectile->SetDir(-90.f + (i-1) * 30);
			projectile->SetSpeed(500.f);
			projectile->SetTexture(m_pTextrue);
		}
		fireTime = 0;
	}
}
