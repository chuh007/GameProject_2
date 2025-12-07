#include "pch.h"
#include "Projectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "IDamageable.h"
#include "SceneManager.h"
#include "PoolManager.h"
PlayerProjectile::PlayerProjectile()
	: m_angle(0.f)
	, m_dir(1.f, 1.f)
	, m_speed(500.f)
	, m_damage(10)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
	auto* col = AddComponent<Collider>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
}

void PlayerProjectile::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();
	//ELLIPSE_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height,
		RGB(255, 0, 255));
	ComponentRender(_hdc);
}

PlayerProjectile::~PlayerProjectile()
{

}

void PlayerProjectile::Update()
{
	//Translate({cosf(m_angle) * 500.f * fDT, sinf(m_angle) * 500.f * fDT});
	Translate({ m_dir.x * m_speed * fDT, m_dir.y * m_speed * fDT });

	if (GetPos().x < -200 || GAME_WIDTH + 200 < GetPos().x ||
		GetPos().y < -200 || GAME_HEIGHT + 200 < GetPos().y)
	{
		GET_SINGLE(PoolManager)->Push<PlayerProjectile>(PoolType::PlayerProj, this);
		GetComponent<Collider>()->SetActive(false);
	}
}

void PlayerProjectile::EnterCollision(Collider* _other)
{
	IDamageable* damageable = dynamic_cast<IDamageable*>(_other->GetOwner());
	if (damageable)
	{
		damageable->TakeDamage(m_damage);
		GET_SINGLE(PoolManager)->Push<PlayerProjectile>(PoolType::PlayerProj, this);
		GetComponent<Collider>()->SetActive(false);
		//GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}

void PlayerProjectile::Reset() {
	m_corutines.clear();
	GetComponent<Collider>()->SetActive(true);
}
