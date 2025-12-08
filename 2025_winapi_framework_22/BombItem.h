#pragma once
#include "Item.h"
class BombItem :
    public Item
{
public:
    void OnCollect() override;
};

