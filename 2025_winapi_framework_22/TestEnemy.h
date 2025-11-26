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

    virtual void TakeDamage(int _damage) override;
    virtual void HPZero() override;
};

