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
#include "StateMachine.h"
#include "IdleState.h"
Player::Player()
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\plane.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	AddComponent<Collider>();
	auto* rb = AddComponent<Rigidbody>();
	rb->SetUseGravity(false);
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

	StateMachine* fsm = AddComponent<StateMachine>();
	assert(fsm != nullptr && "fsm is null in player");
	fsm->ChangeState(new PlayerIdleState());
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

	ComponentRender(_hdc);
}

void Player::StayCollision(Collider* _other)
{
}

void Player::EnterCollision(Collider* _other)
{

}


void Player::ExitCollision(Collider* _other)
{
}


void Player::Update()
{
	//Vec2 dir = {};
	//if (GET_KEY(KEY_TYPE::W)) dir.y -= 1.f;
	//if (GET_KEY(KEY_TYPE::S)) dir.y += 1.f;
	//if (GET_KEY(KEY_TYPE::A)) dir.x -= 1.f;
	//if (GET_KEY(KEY_TYPE::D)) dir.x += 1.f;
	//Translate({dir.x * fDT * 200.f, dir.y * fDT * 200.f});

	// Q, E 크게 작게 
	float scaleDelta = 0.f;
	float scaleSpeed = 1.f;
	if (GET_KEY(KEY_TYPE::Q))
		scaleDelta += scaleSpeed * fDT;
	if (GET_KEY(KEY_TYPE::E))
		scaleDelta -= scaleSpeed * fDT;
	float factor = scaleSpeed + scaleDelta;
	Scale({ factor, factor });
	//if (GET_KEYDOWN(KEY_TYPE::SPACE))
	//	CreateProjectile();
	Object::LateUpdate();
}

void Player::CreateProjectile()
{
	PlayerProjectile* proj = new PlayerProjectile;
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


