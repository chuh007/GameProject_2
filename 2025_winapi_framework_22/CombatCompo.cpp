#include "pch.h"
#include "CombatCompo.h"
#include "InputManager.h"
#include "Player.h"
#include "PoolManager.h"
#include "DeleteBullet.h"

CombatCompo::CombatCompo() : m_projCooldown(0.f), m_bombCnt(0) {

}

CombatCompo::~CombatCompo() {
	
}

void CombatCompo::Init() {
	m_bombCnt = MAX_BOMB_COUNT;
}

void CombatCompo::LateUpdate() {
	if (GET_KEY(KEY_TYPE::Q)) {
		UseBomb();
	}
}

void CombatCompo::Render(HDC _hdc) {

}

void CombatCompo::TryContinueFire(float _fDT) {
	assert(m_projCooldown != NULL && "m_projCooldown is null");
	assert(_fDT != NULL && "fDT is null");
	std::cout << m_projCooldown << " : " << _fDT << std::endl;
	if (GET_KEY(KEY_TYPE::SPACE)) {
		m_projCooldown += _fDT;
		if (m_projCooldown > PROJECTILE_INTERVAL) {
			Player* player = static_cast<Player*>(GetOwner());
			player->CreateProjectile();
			m_projCooldown = 0.f;
		}
	}
}

bool CombatCompo::UseBomb() {
	// PoolManager 써서 Push 해줘야해
	if (m_bombCnt > 0) {
		m_bombCnt--;

		GET_SINGLE(SceneManager)->GetCurScene()->
			AddObject(delBullet, Layer::PROJECTILEDELETER);

		std::cout << "use bomb" << std::endl;
		return true;
	}

	if (delBullet) {
		GET_SINGLE(SceneManager)->RequestDestroy(delBullet);
	}

	std::cout << "no bomb left" << std::endl;
	return false;
}
