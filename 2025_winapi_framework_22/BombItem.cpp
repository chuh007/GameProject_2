#include "pch.h"
#include "BombItem.h"
#include "PlayerManager.h"
void BombItem::OnCollect()
{
	Player* p = GET_SINGLE(PlayerManager)->GetPlayer();
	p->PlusBombCount(1);
}
