#pragma once
#include "Item.h"
class OneUpItem :
    public Item
{
    // Item을(를) 통해 상속됨
    void OnCollect() override;
};

