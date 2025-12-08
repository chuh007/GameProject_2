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
#include "PoolManager.h"
#include "Health.h"
#include "PlayerHitState.h"
#include "PlayerDeadState.h"
#include "DeleteBullet.h"
#include "TimeManager.h"

Player::Player() : m_isDead(false), m_life(3), m_powerLevel(0), m_isInvincible(false),
m_projCooldown(0.f), m_bombCnt(0), m_invincibleTime(0.f), m_bombDurationTimer(0.f),
m_amountDmg(0.f),
col(nullptr), fsm(nullptr), m_health(nullptr),  m_proj(nullptr), delBullet(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Jiwoo");
	auto* rb = AddComponent<Rigidbody>();
	rb->SetUseGravity(false);
	col = AddComponent<Collider>();
	col->SetName(L"Player");
	col->SetSize(5.0f);
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

	m_health = AddComponent<Health>();
	m_health->SetMaxHP(3);
	m_health->SetCurrentHP(3);
	m_bombCnt = MAX_BOMB_COUNT;

	fsm = AddComponent<StateMachine>();
	assert(fsm != nullptr && "fsm is null in player");
	fsm->ChangeState(new PlayerIdleState());
}

Player::~Player()
{
	// 여기 DELETE 해줘야해
	if (delBullet) {
		delete delBullet;
		delBullet = nullptr;
	}
}

void Player::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	ComponentRender(_hdc);

	HPEN hRedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(_hdc, hRedPen);

	HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(_hdc, hNullBrush);

	float centerX = pos.x;
	float centerY = pos.y;

	int x1 = (int)(centerX - HITBOX_RADIUS);
	int y1 = (int)(centerY - HITBOX_RADIUS);
	int x2 = (int)(centerX + HITBOX_RADIUS);
	int y2 = (int)(centerY + HITBOX_RADIUS);

	Ellipse(_hdc, x1, y1, x2, y2);

	SelectObject(_hdc, hOldPen);
	DeleteObject(hRedPen);

	SelectObject(_hdc, hOldBrush);
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
	float _fDT = GET_SINGLE(TimeManager)->GetDT();
	const float BOMB_DURATION = 2.f;

	if (delBullet != nullptr) {
		m_bombDurationTimer += _fDT;
		if (m_bombDurationTimer >= BOMB_DURATION) {
			GET_SINGLE(SceneManager)->RequestDestroy(delBullet);
			delBullet = nullptr;
			m_bombDurationTimer = 0.f;
		}
	}

	if (GET_KEYDOWN(KEY_TYPE::Q)) {
		if (delBullet == nullptr) {
			UseBomb();
		}
	}
	if (GET_KEYDOWN(KEY_TYPE::Z)) {
		if (m_powerLevel <= MAX_POWER) {
			GainPower(1);
		}
	}
	Object::LateUpdate();
}

void Player::CreateProjectile()
{
	int num_proj = 1;
	if (m_powerLevel >= MAX_POWER) {
		num_proj = 5;
	}
	else if (m_powerLevel >= 96) {
		num_proj = 4;
	}
	else if (m_powerLevel >= 64) {
		num_proj = 3;
	}
	else if (m_powerLevel >= 32) {
		num_proj = 2;
	}

	const float ANGLE_STEP = 8.f;
	float start_angle_deg = 0.f;

	if (num_proj > 1) {
		start_angle_deg = -(num_proj - 1) * ANGLE_STEP / 2.f;
	}

	float baseDmg = 10.f;
	float totalDmg = baseDmg + m_amountDmg;

	for (int i = 0; i < num_proj; ++i)
	{
		PlayerProjectile* proj = GET_SINGLE(PoolManager)->
			Pop<PlayerProjectile>(PoolType::PlayerProj);

		proj->Reset();
		Vec2 pos = GetPos();
		pos.y -= GetSize().y / 2.f;
		proj->SetPos(pos);
		proj->SetSize({ 30.f,30.f });

		proj->SetDamage(totalDmg);

		float current_angle_deg = start_angle_deg + (float)i * ANGLE_STEP;
		float current_angle_rad = current_angle_deg * PI / 180.f;

		proj->SetDir({ sinf(current_angle_rad), -cosf(current_angle_rad) });
	}
}

StateMachine* Player::GetStateMachine() const {
	return fsm;
}

bool Player::IsMovingInputProcessed() const {
	return GET_KEY(KEY_TYPE::W) || GET_KEY(KEY_TYPE::A) ||
		GET_KEY(KEY_TYPE::S) || GET_KEY(KEY_TYPE::D);
}

void Player::TakeDamage(int _damage) {
	if (m_isInvincible) return;

	m_health->TakeDamage(_damage);
	if (m_isDead) return;

	cout << "P : " << _damage << endl;
}

void Player::HPZero() {
	m_life--;
	if (m_life > 0) {
		m_health->SetCurrentHP(m_health->GetMaxHP());
		SetPos({ GAME_WIDTH / 2.f, 600.f });
		fsm->ChangeState(new PlayerHitState());
	}
	else {
		m_isDead = true;
		fsm->ChangeState(new PlayerDeadState());
	}
}

void Player::SetInvincible(bool isInvincible) {
	m_isInvincible = isInvincible;
}

float& Player::GetInvincibleTime() {
	return m_invincibleTime;
}

float Player::GetMaxInvincibleTime() const {
	return MAX_INVINCIBLE_TIME;
}

void Player::TryContinueFire(float _fDT) {
	if (GET_KEY(KEY_TYPE::SPACE)) {
		m_projCooldown += _fDT;
		while (m_projCooldown >= PROJECTILE_INTERVAL) {
			CreateProjectile();
			m_projCooldown -= PROJECTILE_INTERVAL;
		}
	}
	else {
		m_projCooldown = 0.f;
	}
}

bool Player::UseBomb() {
	if (m_bombCnt > 0) {
		m_bombCnt--;

		delBullet = new DeleteBullet();
		delBullet->SetPos(GetPos());

		GET_SINGLE(SceneManager)->GetCurScene()->
			Spawn<DeleteBullet>(Layer::PROJECTILEDELETER, GetPos(), GetSize());

		m_bombDurationTimer = 0.f;

		std::cout << "use bomb : " << m_bombCnt << std::endl;
		return true;
	}

	std::cout << "no bomb left or bomb ended" << std::endl;
	return false;
}

void Player::GainPower(int _amount) {
	m_powerLevel += _amount;
	m_amountDmg += 1.f;

	m_powerLevel = std::min(m_powerLevel, MAX_POWER);
	std::cout << "Power Level: " << m_powerLevel << std::endl;
}


