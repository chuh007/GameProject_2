#include "pch.h"
#include "Boss.h"
#include "Health.h"
#include "Collider.h"
#include "BossMover.h"
#include "PatternCompo.h"
#include "SceneManager.h"
#include "CirclePattern.h"
#include "CircleToPlayerPattern.h"
#include "PlayerManager.h"
Boss::Boss()
	: m_lifeCount(2)
	, m_decDamage(1.f)
	, m_target(nullptr)
{
	auto* col = AddComponent<Collider>();
	col->SetSize(50.f);
	m_target = GET_SINGLE(PlayerManager)->GetPlayer();
	m_healthCompo = AddComponent<Health>();
	m_healthCompo->SetMaxHP(100);
	m_healthCompo->SetCurrentHP(100);
	auto* mover = AddComponent<BossMover>();

	m_patternCompo = AddComponent<PatternCompo>();
	m_patternCompo->ResizePattenList(3);

	auto* pattern1 = new CirclePattern(this, m_target, 0.5f, mover);
	m_patternCompo->AddNomalPattern(1, pattern1);
	auto* spell1 = new CircleToPlayerPattern(this, m_target, 0.75f, mover);
	m_patternCompo->AddSpellPattern(1, spell1);

	m_patternCompo->UseNomalPattern();
}

Boss::~Boss()
{
}

void Boss::Update()
{

}

void Boss::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);

	ComponentRender(_hdc);
}

void Boss::EnterCollision(Collider* _other)
{
}

void Boss::TakeDamage(int _damage)
{
	m_healthCompo->TakeDamage(_damage * m_decDamage);
	cout << _damage << endl;
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
	}
	else
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}
