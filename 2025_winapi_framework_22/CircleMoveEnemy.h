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

public:
    void SetShotCount(int count);
protected:

private:
    float fireTime;
    int fireCount;
};

