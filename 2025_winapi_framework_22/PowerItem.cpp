#include "pch.h"
#include "PowerItem.h"
#include "PlayerManager.h"

PowerItem::~PowerItem()
{
	Item::~Item();
}

void PowerItem::OnCollect()
{
	Player* p = GET_SINGLE(PlayerManager)->GetPlayer();
	p->GainPower(1);
}
