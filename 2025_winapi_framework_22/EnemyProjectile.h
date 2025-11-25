#pragma once
#include "Object.h"

class Texture;
class EnemyProjectile :
    public Object
{
public:
    EnemyProjectile();
    virtual ~EnemyProjectile();

public:
    // Object을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

public:
    virtual void Init();

public:
    void SetSpeed(float speed) { m_speed = speed; }
    const float& GetSpeed() const { return m_speed; }
    void SetDir(Vec2 dir) { dir.Normalize(); m_dir = dir; }
    void SetDir(float angle) {
        float delta = angle * D2R;
        m_dir = { cosf(delta), -sinf(delta) };
    }
    const Vec2& GetDir() const { return m_dir; }

protected:
    float m_angle;
    float m_speed;
    Vec2 m_dir;
    Texture* m_pTex;
};

