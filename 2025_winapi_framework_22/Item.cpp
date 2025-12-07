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
