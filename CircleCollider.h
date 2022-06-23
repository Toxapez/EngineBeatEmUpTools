#pragma once
#include "Collider.h"
struct CircleCollider : public Collider
{
	Vector2 originalpos;
	Vector2 pos;
	float radio;
	CircleCollider();
	void Set(Vector2 p, float r, GameObject* g);
	void Update() override;
	void Draw() override;
};

