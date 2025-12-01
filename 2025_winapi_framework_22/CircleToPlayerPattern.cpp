#include "pch.h"
#include "CircleToPlayerPattern.h"
#include "CirclePattern.h"
#include "EnemyProjectile.h"

CircleToPlayerPattern::CircleToPlayerPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover)
	: Pattern(_owner, _target, _patternUseTime, _mover)
	, m_projectileType(PoolType::Circle1)
	, m_fireCount(20)
	, m_speed(250)
{
	m_decValue = 0.5f;
}

CircleToPlayerPattern::~CircleToPlayerPattern()
{
}

void CircleToPlayerPattern::Update()
{
	m_curTime += fDT;
	if (m_curTime > m_patternUseTime)
	{
		m_curTime = 0;
		int x = (rand() % GAME_WIDTH / 2) + GAME_WIDTH / 4;
		int y = (GAME_HEIGHT / 5) + rand() % 100;
		//m_mover->MoveTo({ x,y }, 1.f);
		CirCleToPlayerShoot();
		RayShout();
	}
}

void CircleToPlayerPattern::CirCleToPlayerShoot()
{
	float angle = 360.f / (float)m_fireCount;
	for (int i = 0; i < m_fireCount; ++i)
	{
		auto* projectile = PoolManager::GetInst()->
			Pop<EnemyProjectile>(PoolType::Circle1);
		auto target = m_target;
		float speed = m_speed;
		projectile->SetSize({ 10.f, 10.f });
		projectile->SetColliderSize(7.5f);
		projectile->SetPos(m_owner->GetPos());
		projectile->SetDir(angle * i);
		projectile->SetSpeed(speed);
		projectile->Coroutine([=]()
			{
				projectile->SetDir(target->GetPos() - projectile->GetPos());
				projectile->SetSpeed(speed * 0.75f);
			}, 0.5f);
	}
}

void CircleToPlayerPattern::RayShout()
{
	for (int i = 0; i < 5; ++i)
	{
		auto* projectile = PoolManager::GetInst()->
			Pop<EnemyProjectile>(PoolType::Circle1);
		projectile->SetSize({ 10.f, 10.f });
		projectile->SetColliderSize(7.5f);
		projectile->SetPos({ GAME_WIDTH / 6 * (i + 1), 0 });
		projectile->SetDir({ 0.f, 1.f });
		projectile->SetSpeed(m_speed);
	}
}
