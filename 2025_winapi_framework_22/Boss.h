#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
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
};

