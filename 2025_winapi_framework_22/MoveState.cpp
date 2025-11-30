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
}

void PlayerMoveState::Excute(StateMachine* fsm) {
	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;
	if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;

	m_player->RequestTranslate({ dir.x * fDT * 200.f, dir.y * fDT * 200.f });

	bool isMoving = (dir.x != 0.f || dir.y != 0.f);
	// 계속 Space키를 누르고 있는 상태인가?
	m_player->TryContinueFire(fDT);

	if (!isMoving)
	{
		fsm->ChangeState(new PlayerIdleState());
		return;
	}
}

void PlayerMoveState::Exit(StateMachine* fsm) {
	assert(fsm != nullptr && 
		"PlayerMoveState::Exit StateMachine is nullptr");
}
