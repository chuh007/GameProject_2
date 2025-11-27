#pragma once
#include "Enemy.h"
#include "MathHelper.h"
class TestEnemy :
    public Enemy
{
public :
    TestEnemy();
    ~TestEnemy();

public:
    void SetPath(BezierPathData* path);
private:
    BezierPathData* pathData;
};

