#include "InvisibleWall.h"
Scoper500<InvisibleWall> InvisibleWall::placerScope;

InvisibleWall::InvisibleWall() {
	collider.Set(Vector2(), Vector2(LEVELTILESIZE, LEVELTILESIZE), this);
	collider.layer = 0;
}

void InvisibleWall::EditorDraw() {
	collider.drawable = true;
	
}

void InvisibleWall::AfterStaticStart() {
	castShadow = false;
	for (int i = 0; i < 4; i++) {
		casters.push_back(new ShadowCaster(Line(), this));
		casters[i]->isActive = false;
	}
}


void InvisibleWall::Update() {

}
void InvisibleWall::Draw() {
	if (castShadow)
		collider.Update();
	for (int i = 0; i < 4; i++)
	{
		casters[i]->isActive = castShadow;
		if (castShadow) {
			casters[i]->body = collider.lineas[i];
		}
	}
}

void InvisibleWall::SetSettings() {

}

void InvisibleWall::CollisionsWithAllBlocks(bool b, BoxCollider* c, Vector2* speed, bool* sidesColliding) {
	//if (b) {
	//	for (int i = Collider::colliders.placerScope - 1; i >= 0; i--) {
	//		CollideWithSolidBlock(i, c, speed, sidesColliding);
	//	}
	//}
	//else {
	//	for (int i = 0; i < Collider::colliders.placerScope; i++) {
	//		CollideWithSolidBlock(i, c, speed, sidesColliding);
	//	}
	//}
	Vector2 oriSpeed = *speed;
	c->gameObject->transform.position.y -= oriSpeed.y;
	*speed = Vector2(oriSpeed.x,0);
	for (int i = Collider::colliders.placerScope - 1; i >= 0; i--) {
		Collider* other = Collider::colliders[i];
		if (*other->isActive) {
			if (other->layer == 0 || other->layer == 1) {
				BoxCollider* bOther = (BoxCollider*)other;
				if (ColliderManager::AlignedBoxBoxOverlaping(bOther, c )) {
					Vector2 otherCenter = bOther->GetCenter();
					//Vector2 originalPos = c->GetCenter() - *speed;
					auto cSides = c->GetFourPoints();
					auto otherSides = bOther->GetFourPoints();
					int nearestSide = 0;
					float shortestDistance = ((cSides[0] - *speed) - otherCenter).Magnitude();
					for (int k = 1; k < 4; k++) {
						float d = ((cSides[k] - *speed) - otherCenter).Magnitude();
						if (d < shortestDistance) {
							nearestSide = k;
							shortestDistance = d;
						}
					}
					Vector2 dir = ((*speed) * -1).Normalize();
					float dist1 = 0;
					float dist2 = 0;
					if (dir.x > 0) 
						dist1 = otherSides[3].x - (cSides[nearestSide] - *speed).x;
					else  dist1 =  otherSides[0].x - (cSides[nearestSide] - *speed).x;

					if (dir.y > 0)
						dist2 =  otherSides[3].y - (cSides[nearestSide] - *speed).y;
					else  dist2 =  otherSides[0].y - (cSides[nearestSide] - *speed).y;
					Vector2 centerDif = c->gameObject->transform.position - c->GetCenter();
					c->gameObject->transform.position -= *speed;
					//Console::SendMessage("coli");
					if (sidesColliding) {
						sidesColliding[1] = speed->x > 0;
						sidesColliding[2] = speed->x < 0;
					}
					if ((*speed).Magnitude() > 0) {
						if (abs(dist1) < abs(dist2) && speed->x != 0) {
							float ration = dir.x != 0 ? dir.y / dir.x : 0;
							float residualSpeed = (*speed).Magnitude() * (dir.y < 0 ? 1 : -1);
							Vector2 r = Vector2(Vector2(dist1, dist1 * ration + (dir.y != 0 ? residualSpeed : 0)));
							c->gameObject->transform.position += r;
							//Console::SendMessage(std::to_string(r.x) + "," + std::to_string(r.y) + "|" + std::to_string((*speed).x) + "," + std::to_string((*speed).y));

						}
						else if (abs(dist1) > abs(dist2) && speed->y != 0) {
							float ration = dir.y != 0 ? dir.x / dir.y : 0;
							float residualSpeed = (*speed).Magnitude() * (dir.x < 0 ? 1 : -1);
							Vector2 r = Vector2(dist2 * ration + (dir.x != 0 ? residualSpeed : 0), dist2);
							c->gameObject->transform.position += r;
							//Console::SendMessage(std::to_string(r.x) + "," + std::to_string(r.y) + "|" + std::to_string((*speed).x) + "," + std::to_string((*speed).y));
						}//Console::SendMessage(std::string("nodifdist | ") + std::to_string((*speed).x) + ", " + std::to_string((*speed).y));
					}
					//else Console::SendMessage("nospeed");
				}
			}
		}
	}
	c->gameObject->transform.position.y += oriSpeed.y;
	*speed = Vector2(0, oriSpeed.y);
	for (int i = Collider::colliders.placerScope - 1; i >= 0; i--) {
		Collider* other = Collider::colliders[i];
		if (*other->isActive) {
			if (other->layer == 0 || other->layer == 1) {
				BoxCollider* bOther = (BoxCollider*)other;
				if (ColliderManager::AlignedBoxBoxOverlaping(bOther, c)) {
					Vector2 otherCenter = bOther->GetCenter();
					//Vector2 originalPos = c->GetCenter() - *speed;
					auto cSides = c->GetFourPoints();
					auto otherSides = bOther->GetFourPoints();
					int nearestSide = 0;
					float shortestDistance = ((cSides[0] - *speed) - otherCenter).Magnitude();
					for (int k = 1; k < 4; k++) {
						float d = ((cSides[k] - *speed) - otherCenter).Magnitude();
						if (d < shortestDistance) {
							nearestSide = k;
							shortestDistance = d;
						}
					}
					Vector2 dir = ((*speed) * -1).Normalize();
					float dist1 = 0;
					float dist2 = 0;
					if (dir.x > 0)
						dist1 = otherSides[3].x - (cSides[nearestSide] - *speed).x;
					else  dist1 = otherSides[0].x - (cSides[nearestSide] - *speed).x;

					if (dir.y > 0)
						dist2 = otherSides[3].y - (cSides[nearestSide] - *speed).y;
					else  dist2 = otherSides[0].y - (cSides[nearestSide] - *speed).y;
					Vector2 centerDif = c->gameObject->transform.position - c->GetCenter();
					c->gameObject->transform.position -= *speed;
					//Console::SendMessage("coli");
					if (sidesColliding) {
						sidesColliding[0] = speed->y > 0;
						sidesColliding[3] = speed->y < 0;
					}
					if ((*speed).Magnitude() > 0) {
						if (abs(dist1) < abs(dist2) && speed->x != 0) {
							float ration = dir.x != 0 ? dir.y / dir.x : 0;
							float residualSpeed = (*speed).Magnitude() * (dir.y < 0 ? 1 : -1);
							Vector2 r = Vector2(Vector2(dist1, dist1 * ration + (dir.y != 0 ? residualSpeed : 0)));
							c->gameObject->transform.position += r;
							//Console::SendMessage(std::to_string(r.x) + "," + std::to_string(r.y) + "|" + std::to_string((*speed).x) + "," + std::to_string((*speed).y));

						}
						else if (abs(dist1) > abs(dist2) && speed->y != 0) {
							float ration = dir.y != 0 ? dir.x / dir.y : 0;
							float residualSpeed = (*speed).Magnitude() * (dir.x < 0 ? 1 : -1);
							Vector2 r = Vector2(dist2 * ration + (dir.x != 0 ? residualSpeed : 0), dist2);
							c->gameObject->transform.position += r;
							//Console::SendMessage(std::to_string(r.x) + "," + std::to_string(r.y) + "|" + std::to_string((*speed).x) + "," + std::to_string((*speed).y));
						}//Console::SendMessage(std::string("nodifdist | ") + std::to_string((*speed).x) + ", " + std::to_string((*speed).y));
					}
					//else Console::SendMessage("nospeed");
				}
			}
		}
	}
}

void InvisibleWall::CollideWithSolidBlock(int i, BoxCollider* c, Vector2* speed, bool* sidesColliding) {
	Collider* other = Collider::colliders[i];
	if (*other->isActive) {
		if (other->layer == 0 || other->layer == 1) {
			c->Update();
			if (ColliderManager::CollidingBoxMovBoxSolid(c, (BoxCollider*)other, speed)) {
				sidesColliding[ColliderManager::CollideBoxMovBoxSolid(c, (BoxCollider*)other, speed)] = true;
				i = -1;
			}
		}
	}



}


PlaceableObject* InvisibleWall::Set(Vector2 pos, int ID)  {
	collider.drawable = false;
	collider.Set(Vector2(), Vector2(LEVELTILESIZE, LEVELTILESIZE), this);
	transform.position = pos;
	isActive = true;
	castShadow = false;
	for (int i = 0; i < 4; i++)
		casters[i]->gameobject = this;
	return this;
}
PlaceableObject* InvisibleWall::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}
bool InvisibleWall::AllUsed(){
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}
void InvisibleWall::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}