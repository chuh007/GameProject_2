#pragma once
#include "Object.h"
#include "StateMachine.h"
class Texture;
class Player :
    public Object
{
public:
	Player();
	~Player();
public:
	//virtual void Update();
	//virtual void Render(HDC _hdc);
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
public:
	void RequestTranslate(Vec2 _delta) {
		Translate(_delta);
	}
public:
	void CreateProjectile();
	void TryContinueFire(float _fDT);
	bool IsMovingInputProcessed() const;
private:
	Texture* m_pTex;
	float m_projCooldown = 0.f;
	const float PROJECTILE_INTERVAL = 0.15f; // 총알 연속 발사 간격
};

