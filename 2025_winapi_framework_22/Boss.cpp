#include "pch.h"
#include "Boss.h"
#include "Health.h"
#include "Collider.h"
#include "BossMover.h"
#include "PatternCompo.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "CirclePattern.h"
#include "CircleToPlayerPattern.h"
#include "IcicleFallPattern.h"
#include "GateOfBabylonPattern.h"
#include "PlayerManager.h"
#include "SpiralPattern.h";
#include "PureBulletHellPattern.h"
#include "SecondMagicPattern.h"
#include "MultiSpeedRadialPattern.h";
#include "BoomEffect.h";
#include "PowerItem.h"
Boss::Boss()
	: m_isDie(false)
	, m_lifeCount(5)
	, m_decDamage(1.f)
	, m_target(nullptr)
	, m_backGround(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Boss");
	auto* col = AddComponent<Collider>();
	col->SetSize(40.f);
	m_target = GET_SINGLE(PlayerManager)->GetPlayer();
	m_healthCompo = AddComponent<Health>();
	m_healthCompo->SetMaxHP(5000);
	m_healthCompo->SetCurrentHP(5000);
	auto* mover = AddComponent<BossMover>();

	m_patternCompo = AddComponent<PatternCompo>();
	m_patternCompo->ResizePattenList(m_lifeCount + 1);

	auto* pattern1 = new CirclePattern(this, m_target, 1.2f, mover, L"");
	m_patternCompo->AddNomalPattern(1, pattern1);
	auto* spell1 = new CircleToPlayerPattern(this, m_target, 0.75f, mover, L"구속「부여잡는 올가미」 ");
	m_patternCompo->AddSpellPattern(1, spell1);
	auto* pattern2 = new CirclePattern(this, m_target, 0.75f, mover, L"");
	m_patternCompo->AddNomalPattern(2, pattern2);
	auto* spell2 = new IcicleFallPattern(this, m_target, 0.5f, mover, L"빙설「아이시클 폴」 ");
	m_patternCompo->AddSpellPattern(2, spell2);
	auto* pattern3 = new MultiSpeedRadialPattern(this, m_target, 1.5f, mover, L"");
	m_patternCompo->AddNomalPattern(3, pattern3);
	auto* spell3 = new GateOfBabylonPattern(this, m_target, 0.7f, mover, L"보구「게이트 오브 바빌론」 ");
	m_patternCompo->AddSpellPattern(3, spell3);
	auto* pattern4 = new SpiralPattern(this, m_target, 2.25f, mover, L"");
	m_patternCompo->AddNomalPattern(4, pattern4);
	auto* spell4 = new SecondMagicPattern(this, m_target, 2.5f, mover, L"제 2마법「보석검 젤레치」 ");
	m_patternCompo->AddSpellPattern(4, spell4);
	auto* pattern5 = new SpiralPattern(this, m_target, 1.75f, mover, L"");
	m_patternCompo->AddNomalPattern(5, pattern5);
	auto* spell5 = new PureBulletHellPattern(this, m_target, 0.5f, mover, L"종막「순수한 탄막 지옥」 ");
	m_patternCompo->AddSpellPattern(5, spell5);

}

Boss::~Boss()
{
}


void Boss::Start()
{
	m_patternCompo->UseNomalPattern();
}


void Boss::Update()
{
	if (m_isDie) return;
	Object::Update();
}

void Boss::Render(HDC _hdc)
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

void Boss::EnterCollision(Collider* _other)
{
}

void Boss::TakeDamage(int _damage)
{
	m_healthCompo->TakeDamage(_damage * m_decDamage);
	if (m_isDie) return;
	cout << _damage * m_decDamage << endl;
	if (m_patternCompo->IsUseSpell())
		return;
	if(m_healthCompo->GetHP() <= m_healthCompo->GetMaxHP() * 0.5f)
	{
		m_patternCompo->UseSpellPattern();
		m_decDamage = m_patternCompo->GetCurrentPattern()->GetDecValue();
		GetComponent<BossMover>()->MoveTo({ GAME_WIDTH / 2, GAME_HEIGHT / 4 }, 0.25f);
	}
}

void Boss::HPZero()
{
	m_lifeCount--;
	if (m_lifeCount > 0)
	{
		m_healthCompo->SetCurrentHP(m_healthCompo->GetMaxHP());
		m_patternCompo->UseNomalPattern();
		m_decDamage = m_patternCompo->GetCurrentPattern()->GetDecValue();
		auto* effect = GET_SINGLE(SceneManager)->GetCurScene()
			->Spawn<BoomEffect>(Layer::PROJECTILEDELETER, GetPos(), { 25,25 });
		effect->DoScale(10.f, 0.3f);
		for (int i = 0; i < 10; ++i)
		{
			Vec2 spawnPos = GetPos();
			spawnPos += { rand() % 200 - 100, rand() % 200 - 100 };
			GET_SINGLE(SceneManager)->GetCurScene()
				->Spawn<PowerItem>(Layer::ITEM, spawnPos, { 25,25 });
		}
	}
	else
	{
		auto* effect = GET_SINGLE(SceneManager)->GetCurScene()
			->Spawn<BoomEffect>(Layer::PROJECTILEDELETER, GetPos(), { 25,25 });
		effect->DoScale(20.f, 0.5f);
		m_isDie = true;
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}
