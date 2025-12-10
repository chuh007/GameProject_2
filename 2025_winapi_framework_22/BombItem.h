#pragma once
#include "Item.h"
class BombItem :
    public Item
{
    ~BombItem();
public:
    void OnCollect() override;
};

