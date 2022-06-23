#pragma once
#include "Vector2.h"
#include "Rect.h"
struct Circle
{
	Vector2 pos;
	float radio;
	Circle();
	Circle(Vector2 pos, float radio);
	Rect ToRect();
};

