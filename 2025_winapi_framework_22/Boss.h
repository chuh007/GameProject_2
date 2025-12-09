#pragma once
#include "Object.h"
#include "IDamageable.h"

class PatternCompo;
class Health;
class Texture;
class Boss :
    public Object
    , public IDamageable
{
public:
    Boss();
    ~Boss();

public:
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    virtual void EnterCollision(Collider* _other)override;
public:
    virtual void TakeDamage(int _damage) override;
    virtual void HPZero() override;

public:
    int GetLifeCount()
    {
        return m_lifeCount;
    }
private:
    bool m_isDie;
    int m_lifeCount;
    PatternCompo* m_patternCompo;
    Health* m_healthCompo;
    float m_decDamage;
    Object* m_target;
    Texture* m_pTex;
};

