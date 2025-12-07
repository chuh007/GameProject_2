#pragma once
#include "Object.h"
class Item :
    public Object
{
public:
    Item();
    void Update() override;

protected :
    virtual void OnGetterItem() abstract;
};

