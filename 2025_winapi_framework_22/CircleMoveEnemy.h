#pragma once
#include "Enemy.h"
#include "MathHelper.h"

class CircleMoveEnemy :
    public Enemy
{
public:
    CircleMoveEnemy();
    ~CircleMoveEnemy();
    void Update() override;
protected:

private:
    BezierPathData* pathData;
    float fireTime;
};

