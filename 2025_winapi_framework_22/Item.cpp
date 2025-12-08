#include "pch.h"
#include "Item.h"
#include "Collider.h"
#include "SceneManager.h"

Item::Item()
{
	auto* coll = AddComponent<Collider>();
	coll->SetSize(50.f);
}

void Item::Update()
{
}

void Item::EnterCollision(Collider* _other)
{
	OnCollect();
	GET_SINGLE(SceneManager)->RequestDestroy(this);
}

void Item::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	ELLIPSE_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}
