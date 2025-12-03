#include "pch.h"
#include "Pattern.h"
#include "Object.h"

Pattern::Pattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover)
	: m_curTime(0.f)
	, m_decValue(1.f)
{
	m_owner = _owner;
	m_target = _target;
	m_BaseShoutCooldown = _patternUseTime;
	m_mover = _mover;
}

Pattern::~Pattern()
{
}
