#include "ColliderManager.h"

bool ColliderManager::Colliding(Collider* c1, Collider* c2) {
	if (c1->type == 1) {
		BoxCollider* collider1 = (BoxCollider*)(c1);
		switch (c2->type)
		{
		case 1:
			return CollidingBoxBox(collider1, (BoxCollider*)(c2));
		case 2:
			return CollidingBoxCircle(collider1, (CircleCollider*)(c2));
		case 3:
			return CollidingBoxLine(collider1, (LineCollider*)(c2));
		}
	}
	else if (c1->type == 2) {
		CircleCollider* collider1 = (CircleCollider*)(c1);
		switch (c2->type)
		{
		case 1:
			return CollidingBoxCircle((BoxCollider*)(c2), collider1);
		case 2:
			return CollidingCircleCircle(collider1, (CircleCollider*)(c2));
		case 3:
			return CollidingCircleLine(collider1, (LineCollider*)(c2));
		}
	}
	else if (c1->type == 3) {
		LineCollider* collider1 = (LineCollider*)(c1);
		switch (c2->type)
		{
		case 1:
			return CollidingBoxLine((BoxCollider*)(c2), collider1);
		case 2:
			 return CollidingCircleLine((CircleCollider*)(c2), collider1);
		case 3:
			return CollidingLineLine(collider1, (LineCollider*)(c2));
		}
	}
	return false;
}

bool ColliderManager::CollidingBoxBox(BoxCollider* c1, BoxCollider* c2) {
	if (BoxBoxEdgesInside(c1, c2)) {
		return true;
	}
	if (BoxBoxEdgesInside(c2, c1)) {
		return true;
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (c1->lineas[j] * c2->lineas[i]) {
				if (c1->lineas[j] * c2->lineas[i]) {
					return true;
				}
			}
		}
	}
	return false;
}
//c1 grande // c2 pequeno
bool ColliderManager::BoxBoxEdgesInside(BoxCollider* c1, BoxCollider* c2) {
	c1->Update();
	c2->Update();
	Vector2 vs[] = { c2->lineas[0].points.first,c2->lineas[3].points.second, c2->lineas[0].points.second,c2->lineas[3].points.first };
	Vector2 vs2[] = { c1->lineas[0].points.first ,c1->lineas[3].points.first };
	for (int i = 0; i < 4; i++) {
		Vector2 v = vs[i];
		if (vs2[0].x <= v.x && vs2[0].y <= v.y && v.x <= vs2[1].x && v.y <= vs2[1].y) {
			return true;
		}
	}
	return false;
}

bool ColliderManager::AlignedBoxBoxOverlaping(BoxCollider* c1, BoxCollider* c2) {
	c1->Update();
	c2->Update();
	if(!(c1->lineas[0].points.first.x < c2->lineas[2].points.first.x))return false;
	if(!(c2->lineas[0].points.first.x < c1->lineas[2].points.first.x))return false;
	if(!(c1->lineas[0].points.first.y < c2->lineas[2].points.first.y))return false;
	if(!(c2->lineas[0].points.first.y < c1->lineas[2].points.first.y))return false;
	return true;
}

bool ColliderManager::CollidingBoxMovBoxSolid(BoxCollider* c1, BoxCollider* c2, Vector2* speed) {
	c1->Update();
	BoxCollider c1ColliderPosInicial = BoxCollider(c1->originalPoints.first + *c1->refPos-*speed, c1->originalPoints.second + *c1->refPos-*speed);
	if (CollidingBoxBox(c2,c1)) {
		return true;
	}
	RectFourPoint c1Edges = RectFourPoint(c1ColliderPosInicial.originalPoints.first, c1ColliderPosInicial.originalPoints.second);
	RectFourPoint c1Edges2 = RectFourPoint(c1->originalPoints.first + *c1->refPos, c1->originalPoints.second + *c1->refPos);
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (Line(c1Edges.points[i], c1Edges2.points[i])*c2->lineas[j]) {
				return true;
			}
		}
	}
	return false;
}

int ColliderManager::CollideBoxMovBoxSolid(BoxCollider* c1, BoxCollider* c2, Vector2* speed) {
	c1->gameObject->transform.position -= *speed;
	c1->Update();
	Vector2 center1 = c1->GetCenter();
	Vector2 center2 = c2->GetCenter();
	float angleDir = (center1 - center2).GetAngle();
	bool lineX = false;
	float a = 2 * Meth::PI/3 ;
	float b = Meth::PI / 3;

	if ( a >  abs(angleDir) &&   abs(angleDir) > b) {
		lineX= true;
	}
	float pointLine;
	float w = c1->originalPoints.second.x - c1->originalPoints.first.x;
	float h = c1->originalPoints.second.y - c1->originalPoints.first.y;
	if (lineX) {
		speed->y = 0;
		if (angleDir < 0) {
			pointLine = c2->originalPoints.first.y + c2->refPos->y - h - c1->originalPoints.first.y;
			c1->gameObject->transform.position = Vector2(c1->gameObject->transform.position.x + speed->x, pointLine - 1);
			return 3;
		}
		else {
			pointLine = c2->originalPoints.second.y + c2->refPos->y - c1->originalPoints.first.y;
			c1->gameObject->transform.position = Vector2(c1->gameObject->transform.position.x + speed->x, pointLine + 1);
			return 0;
		}
	}
	else {
		speed->x = 0;
		if (Meth::PI/2 < abs(angleDir)) {
			pointLine = c2->originalPoints.first.x + c2->refPos->x - w - c1->originalPoints.first.x;
			c1->gameObject->transform.position = Vector2(pointLine - 1, c1->gameObject->transform.position.y + speed->y);
			return 2;
		}
		else {
			pointLine = c2->originalPoints.second.x + c2->refPos->x - c1->originalPoints.first.x;
			c1->gameObject->transform.position = Vector2(pointLine + 1, c1->gameObject->transform.position.y + speed->y);
			return 1;
		}
	}
}

bool ColliderManager::CollidingCircleCircle(CircleCollider* c1, CircleCollider* c2) {
	return (c1->pos - c2->pos).Magnitude() < (c1->radio + c2->radio) ;
}
bool ColliderManager::CollidingLineLine(LineCollider* c1, LineCollider* c2) {
	return false;
}
bool ColliderManager::CollidingBoxCircle(BoxCollider* c1, CircleCollider* c2) {
	Vector2 p = Vector2(Meth::Clamp(c2->pos.x, c1->lineas->points.first.x, c1->lineas[3].points.first.x), Meth::Clamp(c2->pos.y, c1->lineas->points.first.y, c1->lineas[3].points.first.y));
	return (p - c2->pos).Magnitude() <= c2->radio;
}
bool ColliderManager::CollidingBoxLine(BoxCollider* c1, LineCollider* c2) {
	for (int i = 0; i < 4; i++) {
		if (c1->lineas[i] * c2->line) {
			return true;
		}
	}
	return false;
}
bool ColliderManager::CollidingCircleLine(CircleCollider* c1, LineCollider* c2) {
	return false;
}

bool ColliderManager::CollidingBoxPoint(BoxCollider* c1, Vector2 c2) {
	if (c1->lineas[0].points.first.x <= c2.x && c1->lineas[0].points.first.y <= c2.y && c2.y <= c1->lineas[3].points.first.y && c2.x <= c1->lineas[3].points.first.x) {
		return true;
	}
	return false;
}