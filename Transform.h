#pragma once
#include "Vector2.h"
class Transform
{
public:
	Vector2 position;
	Vector2 originalPosition;
	Transform(Vector2 position);
	Transform();
	void UpdateOriginalPos() {
		originalPosition = position;
	}

	void RestoreOriginalPos() {
		position = originalPosition;
	}
};

