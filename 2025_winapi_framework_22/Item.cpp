#include "pch.h"
#include "Item.h"
#include "Collider.h"

Item::Item()
{
	auto* coll = AddComponent<Collider>();
	coll->SetSize(GetSize().x);
}

void Item::Update()
{
}

void Item::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	ELLIPSE_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}
