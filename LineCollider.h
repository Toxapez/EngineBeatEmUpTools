#pragma once
#include "Collider.h"
#include "Line.h"
struct LineCollider : public Collider
{
	Line originLine;
	Line line;
	LineCollider();
	void Set(Line l, GameObject* g);
	void Update() override;
	void Draw() override;
};

