#pragma once
#include "Enemy.h"
#include "MathHelper.h"
class TestEnemy :
    public Enemy
{
public :
    TestEnemy();
    ~TestEnemy();

private:
    BezierPathData* pathData;
};

