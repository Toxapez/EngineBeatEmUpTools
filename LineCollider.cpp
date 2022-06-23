#include "LineCollider.h"

LineCollider::LineCollider() {
	type = 3;
}

void LineCollider::Set(Line l, GameObject* g) {
	colliders.GetNextScope() = this;
	originLine = l;
	gameObject = g;
	isActive = &g->isActive;
	refPos = &g->transform.position;
	isActive = &g->isActive;
	Update();
}

void LineCollider::Update() {
	line.points.first = originLine.points.first + *refPos;
	line.points.second = originLine.points.second + *refPos;
}
void LineCollider::Draw() {
	if (drawable) {
	}
}