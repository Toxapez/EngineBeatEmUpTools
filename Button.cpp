#include "Button.h"

Button::Button() {
	state = 0;
	cNormal = Color(50);
	cHover = Color(100);
	cPressed = Color(200);
	cOutline = Color(255);
	ChangeSize(Vector2(20,20));
}

void Button::Update() {


	bool touching = ColliderManager::CollidingBoxPoint(&collider,Mouse::GetVector2PosRef(Cam::currentCam));
	bool clicking = Mouse::leftClickCheck;
	bool clicked = Mouse::leftClickPressed;

	pressing = false;
	pressed = false;

	if (touching) 
		if (clicking) {
			state = 2;
			pressing = true;
			if (clicked)
				pressed = true;
		}
		else state = 1;
	else state = 0;
}
void Button::Draw() {
	FigureDrawer::DrawFillRectRef(Rect(collider.originalPoints.first - collider.originalPoints.second*-.5,collider.originalPoints.second),state == 0 ? cNormal : (state == 1  ? cHover : cPressed),transform);
	FigureDrawer::DrawRectRef(Rect(collider.originalPoints.first - collider.originalPoints.second * -.5, collider.originalPoints.second), cOutline, transform);
}

void Button::ChangeSize(Vector2 v) {
	size = v;
	collider.Set(Vector2(),v, this);
}