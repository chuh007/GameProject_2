#pragma once
#include <vector>
#include "Vec2.h"
//헤더만 있으므로 인클루드 해줘야함

Vec2 Lerf(const Vec2& p0, const Vec2& p1, double t)
{
	Vec2 p;
	p.x = (1.0 - t) * p0.x + t * p1.x;
	p.y = (1.0 - t) * p0.y + t * p1.y;
	return p;
}

Vec2 GetBezierPoint(const std::vector<Vec2>& _points, double t)
{
	int n = _points.size();

	if (n == 0)
		assert(n != 0 && "vector is null!!");
	else if(n==1)
		return _points[0];
	std::vector<Vec2> currentPoints = _points;

	for (int k = 1; k < n; ++k)
	{
		std::vector<Vec2> new_points;

		for (int i = 0; i < n - k; ++i)
		{
			Vec2 p0 = currentPoints[i];
			Vec2 p1 = currentPoints[i + 1];

			new_points.push_back(Lerf(p0, p1, t));
		}
		currentPoints = new_points;
	}

	return currentPoints[0];
}