#pragma once
#include "Component.h"

class CombatCompo : public Component
{
public:
	CombatCompo();
	virtual ~CombatCompo();
public:
	virtual void Init() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
public:
	void TryContinueFire(float _fDT);
	bool UseBomb();
private:
	float m_projCooldown;
	const float PROJECTILE_INTERVAL = 0.15f; // 총알 연속 발사 간격
private:
	int m_bombCnt;
	const int MAX_BOMB_COUNT = 3;
};

