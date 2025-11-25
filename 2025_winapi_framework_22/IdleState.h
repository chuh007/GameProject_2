#pragma once
#include "State.h"
class PlayerIdleState : public State
{
public:
	PlayerIdleState() = default;
	virtual ~PlayerIdleState() = default;
public:
	virtual void Enter(StateMachine* fsm) override;
	virtual void Excute(StateMachine* fsm) override;
	virtual void Exit(StateMachine* fsm) override;
};

