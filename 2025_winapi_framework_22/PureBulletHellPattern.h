#pragma once
#include "Pattern.h"
class PureBulletHellPattern :
    public Pattern
{
public:
    PureBulletHellPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name);
    ~PureBulletHellPattern();

public:
    void Update() override;
    void BaseShoot() override;

private:
    PoolType m_projectileType;
    int m_fireCount;
    int m_speed;
};

