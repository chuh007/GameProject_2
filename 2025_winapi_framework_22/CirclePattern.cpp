#include "pch.h"
#include "CirclePattern.h"
#include "EnemyProjectile.h"

CirclePattern::CirclePattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover)
	: Pattern(_owner, _target, _patternUseTime, _mover)
	, m_projectileType(PoolType::Circle1)
	, m_fireCount(30)
	, m_speed(250)
{
	m_decValue = 1.f;
}

CirclePattern::~CirclePattern()
{
}

void CirclePattern::Update()
{
	m_curTime += fDT;
	if (m_curTime > m_patternUseTime)
	{
		m_curTime = 0;
		int x = (rand() % GAME_WIDTH / 2) + GAME_WIDTH / 4;
		int y = (GAME_HEIGHT / 5) + rand() % 100;
		m_mover->MoveTo({ x,y }, m_patternUseTime);
		CirCleShoot();
	}
}

void CirclePattern::CirCleShoot()
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
	}
}
