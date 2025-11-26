#include "pch.h"
#include "Object.h"
#include "EnemyMovement.h"
#include "MathHelper.h"

void EnemyMovement::Init()
{
}

void EnemyMovement::LateUpdate()
{
	currentTime += fDT;
    GetOwner()->SetPos(GetBezierPoint(points, currentTime));
}

void EnemyMovement::Render(HDC hDC)
{
    PenType colorPen = PenType::MAGENTA;
    GDISelector pen(hDC, colorPen);
    GDISelector brush(hDC, BrushType::HOLLOW);
    if (points.size() < 2) 
    {
        return;
    }

    const int segments = 100; 

    Vec2 first_v = GetBezierPoint(points, 0.0);

    LONG first_x = static_cast<LONG>(std::roundf(first_v.x));
    LONG first_y = static_cast<LONG>(std::roundf(first_v.y));

    MoveToEx(hDC, first_x, first_y, NULL);

    for (int i = 1; i <= segments; ++i)
    {
        double t = (double)i / (double)segments;

        Vec2 v = GetBezierPoint(points, t);

        LONG current_x = static_cast<LONG>(std::roundf(v.x));
        LONG current_y = static_cast<LONG>(std::roundf(v.y));

        LineTo(hDC, current_x, current_y);
    }
}

void EnemyMovement::SetBezierPoints(vector<Vec2>& point)
{
	points = point;
}
