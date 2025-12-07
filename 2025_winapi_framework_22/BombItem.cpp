#include "pch.h"
#include "BombItem.h"

void BombItem::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	ELLIPSE_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}
