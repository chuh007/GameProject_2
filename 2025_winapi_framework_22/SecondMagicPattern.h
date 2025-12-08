#pragma once
#include "Pattern.h"
class SecondMagicPattern :
    public Pattern
{
public:
    SecondMagicPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name);
    ~SecondMagicPattern();

public:
    void Update() override;
    void BaseShoot() override;

private:
};

