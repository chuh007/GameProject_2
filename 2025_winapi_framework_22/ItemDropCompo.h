#pragma once
#include "Component.h"
class ItemDropCompo :
    public Component
{
public:
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
public:
    void SetItem();
};

