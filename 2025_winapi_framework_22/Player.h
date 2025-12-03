#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "Projectile.h"
#include "IDamageable.h"

class Texture;
class Health;
class Player :
    public Object, public IDamageable
{
public:
	Player();
	~Player();
public:
	//virtual void Update();
	//virtual void Render(HDC _hdc);
	void Update() override;
	void Render(HDC _hdc) override;
	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;
public:
	void RequestTranslate(Vec2 _delta) {
		Translate(_delta);
	}
public:
	void CreateProjectile();
	void TryContinueFire(float _fDT);
	bool IsMovingInputProcessed() const;
public:
	virtual void TakeDamage(int _damage) override;
	virtual void HPZero() override;
public:
	int GetLifeCount() {
		return m_life;
	}
private:
	Texture* m_pTex;
	StateMachine* fsm;
	PlayerProjectile* m_proj;
	float m_projCooldown;
	const float PROJECTILE_INTERVAL = 0.15f; // 총알 연속 발사 간격
private:
	Health* m_health;
	Collider* col;
	bool m_isDead;
	int m_life;
};

