#pragma once
#include "Enemy.h"
#include "MathHelper.h"
class TestEnemy :
    public Enemy
{
public :
    TestEnemy();
    ~TestEnemy();
    void Update() override;

private:
    float fireTime = 0;
};

