#pragma once
#include "Component.h"
#include "MathHelper.h" 

class EnemyMovement : public Component
{
private:
    const BezierPathData* m_pathData = nullptr;
    float m_distanceTraveled = 0.0f;
    float m_speed = 0.0f;

public:
    // 기본 생성자만 사용하도록 수정
    EnemyMovement();

    void Init() override;
    // fDT 인자 제거 (매크로 사용)
    void LateUpdate() override;
    void Render(HDC hDC) override;

    void SetPathData(const BezierPathData* path);
    void SetSpeed(float _speed);
};