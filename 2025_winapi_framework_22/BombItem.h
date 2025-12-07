#pragma once
#include "Object.h"
class BombItem :
    public Object
{
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
};

