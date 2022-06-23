#pragma once
#include "Collider.h"
#include "Line.h"
#include "RectFourPoint.h"
#include "Cam.h"
struct BoxCollider : public Collider
{
	std::pair<Vector2, Vector2> originalPoints;
	Line lineas[4];
	Vector2 offset;
	
	BoxCollider();
	BoxCollider(Vector2 p1, Vector2 p2);
	void Set(Vector2 p, Vector2 s, GameObject* g);
	Vector2 GetCenter();
	std::vector<Vector2> GetFourPoints();
	void Update() override;
	void Draw() override;
};

