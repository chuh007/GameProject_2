#include "pch.h"
#include "Object.h"
#include "EnemyMovement.h"

EnemyMovement::EnemyMovement()
{
}

void EnemyMovement::Init()
{
    m_distanceTraveled = 0.0f;
}

void EnemyMovement::LateUpdate()
{
    if (!m_pathData || m_pathData->totalLength <= 0.0f)
    {
        return;
    }

    m_distanceTraveled += m_speed * fDT;

    if (m_distanceTraveled >= m_pathData->totalLength)
    {
        m_distanceTraveled = m_pathData->totalLength;
    }

    double target_t = m_pathData->FindTValueForDistance(m_distanceTraveled);

    Vec2 newPos = GetBezierPoint(m_pathData->points, target_t);

    if (GetOwner()) {
        GetOwner()->SetPos(newPos);
    }
}

void EnemyMovement::SetSpeed(float _speed)
{
    m_speed = _speed;
}

void EnemyMovement::SetPathData(const BezierPathData* path)
{
    m_pathData = path;
    m_distanceTraveled = 0.0f;
}

void EnemyMovement::Render(HDC hDC)
{
    const std::vector<Vec2>& points = m_pathData->points;

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