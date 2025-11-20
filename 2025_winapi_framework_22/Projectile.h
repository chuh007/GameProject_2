#pragma once
#include "Object.h"
class Texture;
class Projectile :
    public Object
{
public:
    Projectile();
    ~Projectile();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC _hdc) override;
public:
    // 인라인 함수
    void SetAngle(float _angle)
    { m_angle = _angle; }
    void SetDir(Vec2 _dir)
    {
        m_dir = _dir;
        m_dir.Normalize();
    }
private:
    //float m_dir;
    float m_angle;
    Vec2 m_dir;
    Texture* m_pTex;
};

