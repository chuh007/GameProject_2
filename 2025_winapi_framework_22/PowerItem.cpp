#include "pch.h"
#include "PowerItem.h"
#include "PlayerManager.h"

void PowerItem::OnCollect()
{
	Player* p = GET_SINGLE(PlayerManager)->GetPlayer();
	p->GainPower(1);
}
