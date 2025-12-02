#include "pch.h"
#include "PlayerDeadState.h"

void PlayerDeadState::Enter(StateMachine* _fsm) {
	std::cout << "Player is dead" << std::endl;
}

void PlayerDeadState::Excute(StateMachine* _fsm){

}

void PlayerDeadState::Exit(StateMachine* _fsm) {
	// 타이틀로 씬 전환 시켜주기
}
