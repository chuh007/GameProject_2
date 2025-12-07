#pragma once
#include "Pattern.h"

class GateOfBabylonPattern :
    public Pattern
{
public:
    GateOfBabylonPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name);
    ~GateOfBabylonPattern();

public:
    // Pattern을(를) 통해 상속됨
    void Update() override;
    void BaseShoot() override;

private:
    int m_basePortalCount;  // 시작 시 마법진 개수
    int m_trailCount;       // 한 번 발사할 때 겹쳐 쏠 탄의 개수 (잔상용, 5개)
    float m_baseSpeed;      // 기본 탄속
};