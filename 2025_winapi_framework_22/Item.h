#pragma once
#include "Object.h"
class Item :
    public Object
{
public:
    Item();
    void Update() override;

protected :
    virtual void OnCollect() abstract;

    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
};

