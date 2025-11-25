#pragma once
#include "Object.h"
#include "IDamageable.h"
class Boss :
    public Object
    , public IDamageable
{
public:
    Boss();
    ~Boss();

public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    virtual void EnterCollision(Collider* _other)override;
public:
    virtual void TakeDamage(int _damage) override;
    virtual void HPZero() override;
private:
    int m_lifeCount;
};

