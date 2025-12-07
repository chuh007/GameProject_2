#include "pch.h"
#include "DeleteBullet.h"
#include "Collider.h"
#include "PoolManager.h"
#include "EnemyProjectile.h"

DeleteBullet::DeleteBullet()
{
	auto* col = AddComponent<Collider>();
	col->SetSize(500.f);
}

DeleteBullet::~DeleteBullet()
{
}

void DeleteBullet::Render(HDC _hdc)
{
}

void DeleteBullet::EnterCollision(Collider* _other)
{
	auto* bullet = static_cast<EnemyProjectile*>(_other->GetOwner());
	bullet->PushSelf();

}
