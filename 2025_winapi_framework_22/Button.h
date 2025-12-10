#pragma once
#include "Object.h"
class Button :
    public Object
{
public:
    ~Button() { Object::~Object(); };
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
    void Update() override;
public:
    virtual void OnClick();
    void SetText(const wstring& str);
private :
    wstring m_text;
};

