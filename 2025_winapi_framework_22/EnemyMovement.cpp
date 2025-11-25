#include "pch.h"
#include "EnemyMovement.h"
#include "MathHelper.h"

void EnemyMovement::Init()
{
}

void EnemyMovement::LateUpdate()
{
	currentTime += fDT;
}

void EnemyMovement::Render(HDC hDC)
{
    std::vector<POINT> pt_array;
    pt_array.reserve(points.size());

    for (const auto& v : points)
    {
        POINT p;

        p.x = static_cast<LONG>(std::roundf(v.x));
        p.y = static_cast<LONG>(std::roundf(v.y));

        pt_array.push_back(p);
    }
    PolyBezier(
        hDC,
        pt_array.data(),
        static_cast<DWORD>(pt_array.size())
    );
}

void EnemyMovement::SetBezierPoints(vector<Vec2>& point)
{
	points = point;
}
