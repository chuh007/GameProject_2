#pragma once
#include "State.h"
class Player;
class CombatCompo;
class PlayerIdleState : public State
{
public:
	PlayerIdleState() = default;
	virtual ~PlayerIdleState() = default;
public:
	virtual void Enter(StateMachine* fsm) override;
	virtual void Excute(StateMachine* fsm) override;
	virtual void Exit(StateMachine* fsm) override;
private:
	Player* m_player = nullptr;
};

