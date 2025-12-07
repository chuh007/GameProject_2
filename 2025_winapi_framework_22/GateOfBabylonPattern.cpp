#include "pch.h"
#include "GateOfBabylonPattern.h"
#include "EnemyProjectile.h"
#include "PoolManager.h"
#include "Effect.h"

// GOB ³Ê³¦
// »ó´Ü ·£´ý À§Ä¡(¸¶¹ýÁø) »ý¼º
// »ý¼ºµÈ Åº¸·Àº ´ë±âÇß´Ù°¡ »çÃâ
// ½ñ¾ÆÁö´Â ´À³¦
// Åº¿¡ ¼ÓµµÂ÷ÀÌ Áà¼­ ÃÒ¶ó¶ô ÇÏ´Â ´À³¦

GateOfBabylonPattern::GateOfBabylonPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name)
	: Pattern(_owner, _target, _patternUseTime, _mover, _name)
	, m_basePortalCount(4) 
	, m_trailCount(5)
	, m_baseSpeed(300.f)
{

	m_decValue = 0.4f;
}

GateOfBabylonPattern::~GateOfBabylonPattern()
{
}

void GateOfBabylonPattern::Update()
{
	Pattern::Update();
	m_curTime += fDT;

	if (m_curTime > m_BaseShoutCooldown)
	{
		m_curTime = 0;
		BaseShoot();
	}
}

void GateOfBabylonPattern::BaseShoot()
{
	GET_SINGLE(ResourceManager)->Play(L"FireSound");

	int currentPortalCount = m_basePortalCount + (int)(m_patternUseTime / 5.0f);
	float currentBaseSpeed = m_baseSpeed + (m_patternUseTime * 10.f);

	for (int i = 0; i < currentPortalCount; ++i)
	{
		Vec2 startPos = { (float)(rand() % GAME_WIDTH), (float)(rand() % (GAME_HEIGHT / 5)) };
		Vec2 targetPos = { (float)(rand() % GAME_WIDTH), (float)(GAME_HEIGHT) };
		Vec2 dir = targetPos - startPos;
		dir.Normalize();

		float randomLaunchDelay = (rand() % 100) / 100.f;

		auto* magicEffect = GET_SINGLE(PoolManager)->Pop<Effect>(PoolType::Effect);

		magicEffect->SetPos(startPos);
		magicEffect->SetSize({ 100.f, 100.f });
		magicEffect->Coroutine([=]()
			{
				GET_SINGLE(PoolManager)->Push<Effect>(PoolType::Effect, magicEffect);
			}, randomLaunchDelay + 0.1f);
		for (int j = 0; j < m_trailCount; ++j)
		{
			auto* projectile = PoolManager::GetInst()->Pop<EnemyProjectile>(PoolType::Circle1);

			projectile->SetSize({ 15.f, 15.f });
			projectile->SetColliderSize(10.f);
			projectile->SetPos(startPos);
			projectile->SetDir(dir);
			projectile->SetSpeed(0.f);

			float finalSpeed = currentBaseSpeed * (1.0f - (j * 0.05f));

			projectile->Coroutine([=]()
				{
					projectile->SetSpeed(finalSpeed);
				}, randomLaunchDelay);
		}
	}
}