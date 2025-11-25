#pragma once
#include "Enemy.h"
class TestEnemy :
    public Enemy
{
public :
    TestEnemy();
    ~TestEnemy();

public:
    void Update() override;
    void Render(HDC _hDC) override;
    virtual void EnterCollision(Collider* _other)override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;

    virtual void TakeDamage(int _damage) override;
    virtual void HPZero() override;
};

