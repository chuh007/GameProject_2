#pragma once
#include "Enemy.h"
#include "MathHelper.h"
class TripleShotEnemy :
    public Enemy
{
public:
    TripleShotEnemy();
    ~TripleShotEnemy();
    void Update() override;
protected:

private:
    BezierPathData* pathData;
    float fireTime;
};

