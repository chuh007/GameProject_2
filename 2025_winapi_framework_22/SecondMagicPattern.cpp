#include "pch.h"
#include "SecondMagicPattern.h"

// 불사「불새 -봉익천상-」 모티브
// 한쪽으로 움직이며, 플레이어를 향해 조준탄 발사
// 조준탄은 크고, 지나간 자리에 랜덤하게 탄막 흩어놓음
// 조준탄 발사와 동시에 원형으로 탄 한번 뿌려줌
// 이걸 3번쯤 반복하며, 한쪽 끝 위치에 도달
// 거기서 원형으로 탄을 5번정도 발사함.
// 동시에 조준탄이 소환한 탄들이 움직이고, 플레이어 조준탄

SecondMagicPattern::SecondMagicPattern(Object* _owner, Object* _target, float _patternUseTime, BossMover* _mover, wstring _name)
    : Pattern(_owner, _target, _patternUseTime, _mover, _name)
{
	m_decValue = 0.4f;
}

SecondMagicPattern::~SecondMagicPattern()
{
}

void SecondMagicPattern::Update()
{
}

void SecondMagicPattern::BaseShoot()
{
}
