#pragma once
#include "BossMover.h"
class Object;
class Pattern
{
public:
	Pattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover);
	virtual ~Pattern();

public:
	virtual void Update() abstract;
	virtual void BaseShoot() abstract;
public:
	float GetDecValue() { return m_decValue; }
protected:
	Object* m_owner;
	Object* m_target;
	float m_BaseShoutCooldown;
	BossMover* m_mover;

	float m_curTime;
	
	float m_decValue;
};

