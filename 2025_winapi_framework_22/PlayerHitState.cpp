#include "pch.h"
#include "Player.h"
#include "PlayerHitState.h"
#include "IdleState.h"
#include "MoveState.h"

void PlayerHitState::Enter(StateMachine* _fsm) {
	m_player = static_cast<Player*>(_fsm->GetOwner());

	std::cout << "Player hit" << std::endl;
}

void PlayerHitState::Excute(StateMachine* _fsm) {
	// 만역 아무런 키 입력이 없다면 -> Idle
	// 입력이 있다면 -> Move
	if (m_player->IsMovingInputProcessed()) {
		_fsm->ChangeState(new PlayerMoveState());
	}
	else {
		_fsm->ChangeState(new PlayerIdleState());
	}

	return;
}

void PlayerHitState::Exit(StateMachine* _fsm) {

}
