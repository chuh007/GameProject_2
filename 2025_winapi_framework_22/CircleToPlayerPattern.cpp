#include "pch.h"
#include "CircleToPlayerPattern.h"
#include "CirclePattern.h"
#include "EnemyProjectile.h"

CircleToPlayerPattern::CircleToPlayerPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover)
	: Pattern(_owner, _target, _patternUseTime, _mover)
	, m_projectileType(PoolType::Circle1)
	, m_fireCount(10)
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
	}
}

void CircleToPlayerPattern::CirCleToPlayerShoot()
{
	float angle = 360.f / (float)m_fireCount;
	for (int i = 0; i < m_fireCount; ++i)
	{
		auto* projectile = PoolManager::GetInst()->
			Pop<EnemyProjectile>(PoolType::Circle1);
		projectile->SetSize({ 10.f, 10.f });
		projectile->SetColliderSize(7.5f);
		projectile->SetPos(m_owner->GetPos());
		projectile->SetDir(angle * i);
		projectile->SetSpeed(m_speed);
		projectile->Coroutine([=]()
			{
				projectile->SetDir(m_target->GetPos() - projectile->GetPos());
				projectile->SetSpeed(m_speed / 2);
			}, 1.f);
	}
}
