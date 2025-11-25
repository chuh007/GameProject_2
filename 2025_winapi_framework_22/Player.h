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
private:
	void CreateProjectile();
private:
	Texture* m_pTex;
};

