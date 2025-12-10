#include "pch.h"
#include "TripleCirclePattern.h"

TripleCirclePattern::TripleCirclePattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name)
	: Pattern(_owner, _target, _patternUseTime, _mover, _name)
	, m_projectileType(PoolType::EnemyProjectile)
	, m_fireCount(30)
	, m_speed(225)
{
	m_bulletTex = GET_SINGLE(ResourceManager)->GetTexture(L"BlueBullet3");
}

TripleCirclePattern::~TripleCirclePattern()
{
	Pattern::~Pattern();
}

void TripleCirclePattern::Update()
{
	Pattern::Update();
	m_curTime += fDT;
	if (m_curTime > m_BaseShoutCooldown)
	{
		m_curTime = 0;
		int x = (rand() % GAME_WIDTH / 2) + GAME_WIDTH / 4;
		int y = (GAME_HEIGHT / 5) + rand() % 100;
		m_mover->MoveTo({ x,y }, m_BaseShoutCooldown);
		BaseShoot();
	}
}

void TripleCirclePattern::BaseShoot()
{

}
