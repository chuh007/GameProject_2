#include "pch.h"
#include "PatternCompo.h"

PatternCompo::PatternCompo()
	: m_curPattern(nullptr)
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
	m_phase++;
	m_curPattern = m_nomalPatternList[m_phase];
	m_isUseSpell = false;
}

void PatternCompo::UseSpellPattern()
{
	m_curPattern = m_spellPatternList[m_phase];
	m_isUseSpell = true;
}
