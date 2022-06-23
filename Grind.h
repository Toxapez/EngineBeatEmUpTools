#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Cam.h"
#include "TextDrawer.h"
#include "FigureDrawer.h"
struct Grind
{
	Vector2 size;
	Vector2 cellSize;
	Color color;
	void Draw(Transform transform);

	std::vector<Vector2> GetCenteredPositions(Transform transform);
};

