#pragma once
#include "Object.h"
#include "IDamageable.h"
class Enemy :
    public Object
    , public IDamageable
{
public:
    Enemy();
    ~Enemy();

public:
    // Object을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    virtual void EnterCollision(Collider* _other)override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;


    // IDamageable을(를) 통해 상속됨
    virtual void TakeDamage(int _damage) override;
    virtual void HPZero() override;

};

