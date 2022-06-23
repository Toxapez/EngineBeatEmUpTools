#include "CamBoundArea.h"

Scoper50<CamBoundArea> CamBoundArea::placerScope;

CamBoundArea::CamBoundArea() {
	needSecondPos = true;
	layer = 20;
	collider.Set(Vector2(),Vector2(),this);
}

PlaceableObject* CamBoundArea::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	collider.Set(Vector2(), camBounds.rect.p2 - camBounds.rect.p1, this);
	camBounds = CameraBounds(RectTwoPoint(transform.position, secondPos));
	return this;
}

void CamBoundArea::Update() {
	if (ColliderManager::BoxBoxEdgesInside(&collider , &Player::player.bodyCollider)) {
		Player::player.cam.cameraBounds = &camBounds;
	}
}

void CamBoundArea::EditorDraw() {
	FigureDrawer::DrawRectRef(Rect((camBounds.rect.p2 - camBounds.rect.p1) * Cam::currentCam->zoom),Color(255,0,0),transform.position, false);
}

void CamBoundArea::SetSecondPos(Vector2 pos) {
	secondPos = pos;
	camBounds = CameraBounds(RectTwoPoint(transform.position, secondPos));
}