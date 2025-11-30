#pragma once
#include "Pattern.h"
#include "PoolManager.h"
class CirclePattern :
    public Pattern
{
public:
    CirclePattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover);
    ~CirclePattern();

public:
    // Pattern을(를) 통해 상속됨
    void Update() override;

public:
    void CirCleShoot();

private:
    PoolType m_projectileType;
    int m_fireCount;
    int m_speed;
};

