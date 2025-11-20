#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Rigidbody.h"
Player::Player()
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\plane.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	AddComponent<Collider>();
	AddComponent<Rigidbody>();
	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"JiwooFront",
		m_pTex, 
		{0.f,150.f},
		{50.f,50.f},
		{50.f,0.f},
		5,0.1f
	);
	animator->Play(L"JiwooFront");
}

Player::~Player()
{
	// DELETE
}
void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	//RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	// blt 5총사 
	// 1. bitblt - 가장 빠른 대신 무식합니다. 
	//::BitBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, width
	//	, height
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, SRCCOPY);

	////// 2. Transparent - 색깔을 뺄 수 있음
	//::TransparentBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0,width, height,
	//	RGB(255,0,255));

	////// 3. StretchBlt - 확대, 축소, 반전
	//::StretchBlt(_hdc
	//	, (int)(pos.x - size.x / 2)
	//	, (int)(pos.y - size.y / 2)
	//	, size.x
	//	, size.y
	//	, m_pTex->GetTextureDC()
	//	, 0, 0, width, height,SRCCOPY);

	//// 4. 회전
	//::PlgBlt()
	//
	
	//// 5. 
	//::AlphaBlend()
	ComponentRender(_hdc);
}

void Player::StayCollision(Collider* _other)
{
}

void Player::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Floor")
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGrounded(true);
	}
}


void Player::ExitCollision(Collider* _other)
{
}


void Player::Update()
{
	//Vec2 pos = GetPos();

	//if (GET_KEY(KEY_TYPE::W))
	//	pos.y -= 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::S))
	//	pos.y += 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::A))
	//	pos.x -= 200.f * fDT;
	//if (GET_KEY(KEY_TYPE::D))
	//	pos.x += 200.f * fDT;
	//SetPos(pos);

	Vec2 dir = {};
	if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;
	if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;
	Translate({dir.x * fDT * 200.f, dir.y * fDT * 200.f});

	// Q, E 크게 작게 
	float scaleDelta = 0.f;
	float scaleSpeed = 1.f;
	if (GET_KEY(KEY_TYPE::Q))
		scaleDelta += scaleSpeed * fDT;
	if (GET_KEY(KEY_TYPE::E))
		scaleDelta -= scaleSpeed * fDT;
	float factor = scaleSpeed + scaleDelta;
	Scale({ factor, factor });
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
		CreateProjectile();
}

void Player::CreateProjectile()
{
	Projectile* proj = new Projectile;
	Vec2 pos = GetPos();
	pos.y -= GetSize().y / 2.f;
	proj->SetPos(pos);
	proj->SetSize({ 30.f,30.f });
	//static float angle = 0.f;
 	//proj->SetAngle(angle * PI / 180.f);
	//angle += 10.f;
	proj->SetDir({0.f, -1.f});
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::PROJECTILE);
	
}


