#include "pch.h"
#include "IdleState.h"
#include "StateMachine.h"
#include "Player.h"
#include "MoveState.h"
#include "PlayerAttackState.h"
#include "InputManager.h"

void PlayerIdleState::Enter(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerIdleState::Enter called with a nullptr StateMachine.");

	m_player = static_cast<Player*>(fsm->GetOwner());
	assert(m_player != nullptr && 
		"StateMachine's owner object is nullptr. Check SetOwner");

	if (m_player) {
		// Idle 애니메이션 재생
	}
	std::cout << "Enter Idle State" << std::endl;
}

void PlayerIdleState::Excute(StateMachine* fsm) {
	// 상태 전이 검사 해주기
	assert(fsm != nullptr && 
		"IdlelState::Excute called with a nullptr StateMachine");
	assert(m_player != nullptr && 
		"StateMachine's Owner object is nullptr");

	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		fsm->ChangeState(new PlayerAttackState());
		return;
	}

	bool isInputW = GET_KEY(KEY_TYPE::W);
	bool isInputS = GET_KEY(KEY_TYPE::S);
	bool isInputA = GET_KEY(KEY_TYPE::A);
	bool isInputD = GET_KEY(KEY_TYPE::D);

	if (isInputW || isInputS || isInputA || isInputD)
	{
		fsm->ChangeState(new PlayerMoveState());
		return;
	}
}

void PlayerIdleState::Exit(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerIdleState::Exit called with a nullptr StateMachine");

	std::cout << "Exiting Idle State" << std::endl;
}
