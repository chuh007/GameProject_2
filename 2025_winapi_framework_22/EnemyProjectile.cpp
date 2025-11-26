#include "pch.h"
#include "EnemyProjectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "IDamageable.h"
#include "SceneManager.h"

EnemyProjectile::EnemyProjectile()
	: m_angle(0.f)
	, m_dir(0.f, 0.f)
	, m_speed(500.f)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"EnemyBullet1");
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::Init()
{

}

void EnemyProjectile::Update()
{
}

void EnemyProjectile::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();
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
