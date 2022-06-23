#include "BoxCatcherUI.h"

BoxCatcherUI::BoxCatcherUI() {
	pressed = false;
	collider.Set(Vector2(), Vector2(), this);
	layer = 9;
	texture = nullptr;

	enabled = false;
	boxCatched = Rect();
	hasMadeChange = false;
	mode = 0;
}
void BoxCatcherUI::Set(Vector2 p, Rect b) {
	transform.position = p;
	body = b;
	collider.Set(Vector2(), Vector2(body.w, body.h), this);
	size = Vector2(body.w, body.h);
}

void BoxCatcherUI::Update() {
	bool hover = false;
	hasMadeChange = false;

	if (enabled) {
		hover = ColliderManager::CollidingBoxPoint(&collider, Mouse::GetVector2PosRef(Cam::currentCam));
	}

	if (!pressed) {

		if (Mouse::leftClickPressed) {
			pressed = hover;
			if (pressed) {
				Mouse::leftClickPressed = false;
				Vector2 corner = transform.position - size / 2;
				firstPos = Mouse::GetVector2PosRef(Cam::currentCam) - corner;
			}
		}

	}
	else {
		Vector2 corner = transform.position - size / 2;
		secondPos = Mouse::GetVector2PosRef(Cam::currentCam) - corner;
		if (!Mouse::leftClickCheck) {

			if (hover) {
				boxCatched = Rect(corner + firstPos, secondPos - firstPos);
				offset = firstPos + texture->size / 2 - size;
				hasMadeChange = true;
				pressed = false;
			}
			else {
				pressed = false;
				hasMadeChange = true;
				boxCatched = Rect();
				offset = Vector2();
			}
		}
	}


}
void BoxCatcherUI::Draw() {
	FigureDrawer::DrawFillRect(body + transform.position, Color(255), false);
	FigureDrawer::DrawRect(body + transform.position, Color(0), false);
	FigureDrawer::DrawLineRef(Line(Vector2(Vector2(size.x,0)/2 * -1), 
		Vector2(size.x, 0) / 2),Color(0),transform.position + size / 2);
	FigureDrawer::DrawLineRef(Line(Vector2(Vector2(0, size.y) / 2 * -1),
		Vector2(0, size.y) / 2), Color(0), transform.position + size / 2);
	if (texture) {
		if (mode == 1) {
			texture->Draw(transform.position + texture->size/2);
		}
		else if (mode == 2 && boxCatched != Rect()) {
			Vector2 corner = transform.position - size / 2;
			texture->Draw(corner + texture->size / 2 + firstPos);
		}
		else {
			texture->Draw(transform.position + size / 2);
		}
	}

		

	if (!pressed) {

		if (boxCatched != Rect()) {
			Vector2 corner = transform.position - size / 2;
			Rect r = Rect(corner + firstPos, secondPos - firstPos);
			FigureDrawer::DrawRect(r + Vector2(r.w, r.h) / 2, Color(255, 0, 0));
		}
	}
	else {
		Vector2 corner = transform.position - size / 2;
		Rect r = Rect(corner + firstPos, secondPos - firstPos );
		FigureDrawer::DrawRect(r + Vector2(r.w,r.h)/2, Color(255, 0, 0));
	}
}

void BoxCatcherUI::Clear() {
	boxCatched = Rect();
	hasMadeChange = false;
	offset = Vector2();
	texture = nullptr;
}