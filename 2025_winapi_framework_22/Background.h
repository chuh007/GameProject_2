#pragma once
#include "Object.h"

class Texture;
class Background :
    public Object
{
public:
    Background();
public:
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;

private:
    Texture* m_pTex;
};

