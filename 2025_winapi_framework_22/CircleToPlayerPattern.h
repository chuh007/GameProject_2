#pragma once
#include "Pattern.h"
class CircleToPlayerPattern :
    public Pattern
{
public:
    CircleToPlayerPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover);
    ~CircleToPlayerPattern();

public:
    // Pattern을(를) 통해 상속됨
    void Update() override;
    void BaseShoot() override;

private:
    void RayShout();

private:
    PoolType m_projectileType;
    int m_fireCount;
    int m_speed;
};

