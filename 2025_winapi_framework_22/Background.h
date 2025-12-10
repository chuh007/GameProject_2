#pragma once
#include "Object.h"

class Texture;
class Background :
    public Object
{
public:
    Background();
    ~Background();
public:
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
    void SetTexture(Texture* _tex) { m_pTex = _tex; }
private:
    Texture* m_pTex;
};

