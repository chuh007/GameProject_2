#pragma once
#include "State.h"
class PlayerMoveState : public State
{
public:
	PlayerMoveState() = default;
	virtual ~PlayerMoveState() = default;
public:
	virtual void Enter(StateMachine* fsm) override;
	virtual void Excute(StateMachine* fsm) override;
	virtual void Exit(StateMachine* fsm) override;
private:
	float m_moveSpeed = 100.f;
};

