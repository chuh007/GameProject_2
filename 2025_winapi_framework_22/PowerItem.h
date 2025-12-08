#pragma once
#include "Item.h"
class PowerItem :
    public Item
{
    // Item을(를) 통해 상속됨
    void OnCollect() override;
};

