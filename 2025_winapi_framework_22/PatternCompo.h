#pragma once
#include "Component.h"
#include "Pattern.h"
class PatternCompo :
    public Component
{
public:
    PatternCompo();
    ~PatternCompo();

public:
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;

public:
    bool IsUsingPattern() { return m_usingPattern; }
    bool IsUseSpell() { return m_isUseSpell; }
    Pattern* GetCurrentPattern() { return m_curPattern; }
    void ResizePattenList(int size)
    {
        m_nomalPatternList.resize(size);
        m_spellPatternList.resize(size);
    }
    void AddNomalPattern(int phase, Pattern* pattern)
    {
        m_nomalPatternList[phase] = pattern;
    }
    void AddSpellPattern(int phase, Pattern* pattern)
    {
        m_spellPatternList[phase] = pattern;
    }
public:
    void UseNomalPattern();
    void UseSpellPattern();
    void DeleteProjectile();
private:
    Pattern* m_curPattern;
    vector<Pattern*> m_nomalPatternList;
    vector<Pattern*> m_spellPatternList;
    bool m_usingPattern;
    bool m_isUseSpell;
    int m_phase;
};

