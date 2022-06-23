#pragma once
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "Meth.h"
struct ColliderManager
{
	static bool Colliding(Collider* c1, Collider* c2);
	static bool CollidingBoxMovBoxSolid(BoxCollider* c1, BoxCollider* c2, Vector2* speed);
	static int CollideBoxMovBoxSolid(BoxCollider* c1, BoxCollider* c2, Vector2* speed);
	static bool CollidingBoxBox(BoxCollider* c1, BoxCollider* c2);
	static bool BoxBoxEdgesInside(BoxCollider* c1, BoxCollider* c2);
	static bool AlignedBoxBoxOverlaping(BoxCollider* c1, BoxCollider* c2);
	static bool CollidingCircleCircle(CircleCollider* c1, CircleCollider* c2);
	static bool CollidingLineLine(LineCollider* c1, LineCollider* c2);
	static bool CollidingBoxCircle(BoxCollider* c1, CircleCollider* c2);
	static bool CollidingBoxLine(BoxCollider* c1, LineCollider* c2);
	static bool CollidingCircleLine(CircleCollider* c1, LineCollider* c2);
	static bool CollidingBoxPoint(BoxCollider* c1,Vector2 c2);
};

