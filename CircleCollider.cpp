#include "CircleCollider.h"

CircleCollider::CircleCollider() {
	colliders.GetNextScope() = this;
	type = 2;
	isActive = nullptr;
}

void CircleCollider::Set(Vector2 p, float r, GameObject* g) {
	type = 2;
	originalpos = p;
	radio = r;
	gameObject = g;
	isActive = &g->isActive;
	Update();
}

void CircleCollider::Update() {
	pos = originalpos + gameObject->transform.position;
}

void CircleCollider::Draw() {
	if (drawable) {
		FigureDrawer::DrawLine(Line(Vector2(pos.x - radio, pos.y), Vector2(pos.x + radio, pos.y)), Color(255));
		FigureDrawer::DrawLine(Line(Vector2(pos.x, pos.y - radio), Vector2(pos.x, pos.y + radio)), Color(255));
	}
}