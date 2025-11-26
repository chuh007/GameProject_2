#include "pch.h"
#include "PlayerAttackState.h"
#include "StateMachine.h"
#include "Player.h"
#include "IdleState.h"
#include "InputManager.h"

void PlayerAttackState::Enter(StateMachine* fsm) {
	m_player = static_cast<Player*>(fsm->GetOwner());

	m_attackTimer = 0.f;
	m_projectileCooltime = 0.f;
	// 애니메이션 재생

	// 공격 판정 처리
	m_player->CreateProjectile();

	std::cout << "Entering Attack State" << std::endl;
}

void PlayerAttackState::Excute(StateMachine* fsm) {
	m_projectileCooltime += fDT;
	if (GET_KEYDOWN(KEY_TYPE::SPACE)) {
		m_attackTimer = 0.f;
		if (m_attackTimer >= PROJECTILE_INTERVAL) {
			m_player->CreateProjectile();
			m_projectileCooltime = 0.f;
		}
	}
	else {
		m_attackTimer += fDT;
	}

	if (m_attackTimer >= 0.1f) {
		fsm->ChangeState(new PlayerIdleState());
		return;
	}
}

void PlayerAttackState::Exit(StateMachine* fsm) {
	// 공격 종료

	std::cout << "Exiting Attack State" << std::endl;
}
