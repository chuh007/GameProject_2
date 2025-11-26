#pragma once
#include "Component.h"
class PatternCompo :
    public Component
{
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
};

