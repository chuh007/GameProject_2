#pragma once
#include "State.h"
class PlayerHitState : public State
{
public:
	PlayerHitState() = default;
	virtual ~PlayerHitState() = default;
public:
	virtual void Enter(StateMachine* _fsm) override;
	virtual void Excute(StateMachine* _fsm) override;
	virtual void Exit(StateMachine* _fsm) override;
private:
	Player* m_player = nullptr;
};

