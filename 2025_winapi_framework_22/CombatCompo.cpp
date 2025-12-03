#include "pch.h"
#include "CombatCompo.h"
#include "InputManager.h"
#include "Player.h"
#include "PoolManager.h"

CombatCompo::CombatCompo() : m_projCooldown(0.f), m_bombCnt(0) {

}

CombatCompo::~CombatCompo() {

}

void CombatCompo::Init() {
	m_bombCnt = MAX_BOMB_COUNT;
}

void CombatCompo::LateUpdate() {
	if (GET_KEYDOWN(KEY_TYPE::Q)) {
		UseBomb();
	}
}

void CombatCompo::Render(HDC _hdc) {

}

void CombatCompo::TryContinueFire(float _fDT) {
	m_projCooldown += _fDT;
	if (m_projCooldown > PROJECTILE_INTERVAL) {

		m_projCooldown = 0.f;
	}
}

bool CombatCompo::UseBomb() {
	// PoolManager 써서 Push 해줘야해

	return false;
}
