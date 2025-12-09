#include "pch.h"
#include "PatternCompo.h"
#include "SceneManager.h"
#include "DeleteBullet.h"
#include "Boss.h"

PatternCompo::PatternCompo()
	: m_curPattern(nullptr)
	, m_spellNameText(nullptr)
	, m_usingPattern(false)
	, m_isUseSpell(false)
	, m_phase(0)
{
}

PatternCompo::~PatternCompo()
{
	for (auto* pattern : m_nomalPatternList)
	{
		SAFE_DELETE(pattern);
	}
	m_nomalPatternList.clear();
	for (auto* pattern : m_spellPatternList)
	{
		SAFE_DELETE(pattern);
	}
	m_spellPatternList.clear();
}

void PatternCompo::Init()
{
	m_spellNameText = GET_SINGLE(SceneManager)->GetCurScene()
		->Spawn<SpellNameText>(Layer::UI, { 0,0 }, { 10.f,10.f });
}

void PatternCompo::LateUpdate()
{
	if (m_curPattern == nullptr) return;
	m_curPattern->Update();
}

void PatternCompo::Render(HDC hDC)
{
}

void PatternCompo::UseNomalPattern()
{
	DeleteProjectile();
	auto owner = dynamic_cast<Boss*>(GetOwner());
	owner->GetBackground()
		->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"Background"));
	GET_SINGLE(ResourceManager)->Play(L"SpellEndSound");
	m_phase++;
	m_curPattern = m_nomalPatternList[m_phase];
	m_isUseSpell = false;
	auto* text = m_spellNameText;
	text->MoveTo({ GAME_WIDTH + 20, 25 }, 0.25f);
}

void PatternCompo::UseSpellPattern()
{
	DeleteProjectile();
	GET_SINGLE(ResourceManager)->Play(L"SpellSound");
	auto owner = dynamic_cast<Boss*>(GetOwner());
	owner->GetBackground()
		->SetTexture(GET_SINGLE(ResourceManager)->GetTexture(L"SpellBackground"));
	m_curPattern = m_spellPatternList[m_phase];
	m_isUseSpell = true;
	auto* text = m_spellNameText;
	int textSize = m_curPattern->GetName().size();
	text->SetName(m_curPattern->GetName());
	text->SetPos({ GAME_WIDTH + 20, GAME_HEIGHT - 50 });
	text->MoveTo({ GAME_WIDTH - 14 * textSize, GAME_HEIGHT - 50 }, 0.5f);
	text->Coroutine([=]()
		{
			text->MoveTo({ GAME_WIDTH - 14 * textSize, 25 }, 1.f);
		}, 0.75f);
	
}

void PatternCompo::DeleteProjectile()
{
	auto* obj = GET_SINGLE(SceneManager)->GetCurScene()
		->Spawn<DeleteBullet>(Layer::PROJECTILEDELETER,
			{ GAME_WIDTH / 2 , GAME_HEIGHT / 2 },
			{ 500,500 });
	obj->Coroutine([=]()
		{
			GET_SINGLE(SceneManager)->GetCurScene()->RequestDestroy(obj);
		}, 0.2f);
}
