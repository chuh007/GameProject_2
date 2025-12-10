#include "pch.h"
#include "OneUpItem.h"
#include "PlayerManager.h"

void OneUpItem::OnCollect()
{
	GET_SINGLE(PlayerManager)->GetPlayer()->PlusLifeCount(1);
}
