#include "BoxCollider.h"

BoxCollider::BoxCollider() {
	colliders.GetNextScope()= this;
	type = 1;
	refPos = nullptr;
}

BoxCollider::BoxCollider(Vector2 p1, Vector2 p2) {
	type = 1;
	originalPoints = std::pair(p1, p2);
	refPos = nullptr;
	gameObject = nullptr;
	isActive = nullptr;
	Update();
}

void BoxCollider::Set(Vector2 p, Vector2 s, GameObject* g) {
	type = 1;
	originalPoints = std::pair(p,s);
	refPos = nullptr;
	gameObject = nullptr;
	isActive = nullptr;
	if (g) {
		refPos = &g->transform.position;
		gameObject = g;
		isActive = &g->isActive;
	}
	Update();
}

void BoxCollider::Update() {
	Vector2 pos1 = originalPoints.first;
	Vector2 pos2 = originalPoints.second ;
	if (refPos) {
		pos1 += *refPos;
		pos2 += *refPos;
	}
	pos1 += offset;
	pos2 += offset;
	lineas[0] = Line(pos1, Vector2(pos1.x, pos2.y));
	lineas[1] = Line(pos1, Vector2(pos2.x, pos1.y));
	lineas[2] = Line(pos2, Vector2(pos1.x, pos2.y));
	lineas[3] = Line(pos2, Vector2(pos2.x, pos1.y));
}

void BoxCollider::Draw() {
	if (drawable) {
		Vector2 pos1 = originalPoints.first* Cam::currentCam->zoom;
		Vector2 pos2 = originalPoints.second * Cam::currentCam->zoom;
		if (refPos) {
			pos1 += *refPos;
			pos2 += *refPos;
		}
		pos1 += offset;
		pos2 += offset;
		Line lineasD[4];
		lineasD[0] = Line(pos1, Vector2(pos1.x, pos2.y));
		lineasD[1] = Line(pos1, Vector2(pos2.x, pos1.y));
		lineasD[2] = Line(pos2, Vector2(pos1.x, pos2.y));
		lineasD[3] = Line(pos2, Vector2(pos2.x, pos1.y));
		Color c = Color(255);
		for (int i = 0; i < 4; i++) {
			FigureDrawer::DrawLine(lineasD[i],c);
		}
	}
}

Vector2 BoxCollider::GetCenter() {
	float w = originalPoints.second.x - originalPoints.first.x;
	float h = originalPoints.second.y - originalPoints.first.y;
	Vector2 r = Vector2(originalPoints.first.x + w / 2, originalPoints.first.y + h / 2);
	if (refPos) {
		r += *refPos;
	}
	return  r;
}

std::vector<Vector2> BoxCollider::GetFourPoints() {
	std::vector<Vector2> r;
	r.push_back(originalPoints.first + *refPos);
	r.push_back(Vector2(originalPoints.second.x, originalPoints.first.y) + *refPos);
	r.push_back(Vector2(originalPoints.first.x, originalPoints.second.y) + *refPos);
	r.push_back(originalPoints.second + *refPos);
	return r;
}