#pragma once
#include "Vector2.h"
#include <utility>
#include "Meth.h"
struct Line
{
	std::pair<Vector2, Vector2> points;
	Line();
	Line(Vector2 p1, Vector2 p2);
	bool operator*(Line other);
	bool SideToSide(Line other);
	static bool CrossLinePoint(Line l1 , Line l2, Vector2* vr);
};

