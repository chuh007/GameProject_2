#pragma once
#include "Component.h"
class EnemyMovement :
    public Component
{
public:
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    bool GetEnded() { return isEnded; };
public:
    void SetBezierPoints(vector<Vec2>& point);
private:
    vector<Vec2> points;
    float movingTime;
    float currentTime;
    bool isEnded;
};

