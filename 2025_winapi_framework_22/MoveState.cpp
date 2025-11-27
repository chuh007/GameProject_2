#include "pch.h"
#include "MoveState.h"
#include "StateMachine.h"
#include "Player.h"
#include "IdleState.h"
#include "PlayerAttackState.h"
#include "InputManager.h"

void PlayerMoveState::Enter(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerMoveState::Enter StateMachine is nullptr");

	m_player = static_cast<Player*>(fsm->GetOwner());
	assert(m_player != nullptr, 
		"PlayerMoveState::Enter Owner Obejct is nullptr");

	// 애니메이션 재생해준다
	std::cout << "Entering Move State" << std::endl;
}

void PlayerMoveState::Excute(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerMoveState::Excute StateMachine is nullptr");
	assert(m_player != nullptr && 
		"PlayerMoveState::Excute Player is nullptr");

	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;
	if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;

	m_player->RequestTranslate({ dir.x * fDT * 200.f, dir.y * fDT * 200.f });

	bool isMoving = (dir.x != 0.f || dir.y != 0.f);

	if (GET_KEYDOWN(KEY_TYPE::SPACE)) {
		fsm->ChangeState(new PlayerAttackState());
		return;
	}

	if (!isMoving)
	{
		fsm->ChangeState(new PlayerIdleState());
		return;
	}
}

void PlayerMoveState::Exit(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerMoveState::Exit StateMachine is nullptr");
	//player->StopMove(); // 움직임 제어 함수 만들기

	std::cout << "Exiting Move State" << std::endl;
}
