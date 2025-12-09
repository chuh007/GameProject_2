#include "pch.h"
#include "PureBulletHellPattern.h"
#include "EnemyProjectile.h"

PureBulletHellPattern::PureBulletHellPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name)
    : Pattern(_owner, _target, _patternUseTime, _mover, _name)
	, m_projectileType(PoolType::EnemyProjectile)
	, m_fireCount(50)
	, m_speed(150)
{
	m_decValue = 0.4f;
	m_bulletTex = GET_SINGLE(ResourceManager)->GetTexture(L"BlueBullet1");
}

PureBulletHellPattern::~PureBulletHellPattern()
{
}

void PureBulletHellPattern::Update()
{
	Pattern::Update();
	m_curTime += fDT;
	if (m_curTime > m_BaseShoutCooldown)
	{
		m_curTime = 0;
		int x = (rand() % 300) + GAME_WIDTH / 2 - 150;
		int y = (GAME_HEIGHT / 4);
		m_mover->MoveTo({ x,y }, m_BaseShoutCooldown);
		BaseShoot();
	}
}

void PureBulletHellPattern::BaseShoot()
{
	float angle = 360.f / (float)m_fireCount;
	GET_SINGLE(ResourceManager)->Play(L"FireSound");
	for (int i = 0; i < m_fireCount; ++i)
	{
		auto* projectile = PoolManager::GetInst()->
			Pop<EnemyProjectile>(PoolType::EnemyProjectile);
		projectile->SetSize({ 55.f, 55.f });
		projectile->SetColliderSize(25.f);
		projectile->SetTexture(m_bulletTex);
		projectile->SetPos(m_owner->GetPos());
		projectile->SetDir(angle * i);
		projectile->SetSpeed(m_speed);
	}
}
