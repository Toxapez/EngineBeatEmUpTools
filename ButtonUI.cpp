#include "ButtonUI.h"

ButtonUI::ButtonUI() {
	pressed = false;
	collider.Set(Vector2(), Vector2(), this);
	layer = 9;

	outLineColor = Color(200);
	color = Color(50);
	hoverOutLineColor = Color(100);
	hoverColor = Color(100);
	pressedOutLineColor = Color(50);
	pressedColor = Color(200);
	disabledOutLineColor = Color(50);
	disabledColor = Color(20);

	enabled = true;
}

void ButtonUI::Set(Vector2 p, Rect b) {
	transform.position = p;
	body = b;
	collider.Set(Vector2(), Vector2(body.w, body.h), this);
	size = Vector2(body.w, body.h);
}

void ButtonUI::Update() {
	pressed = false;
	bool hover = false;

	hover = ColliderManager::CollidingBoxPoint(&collider, Mouse::GetVector2PosRef(Cam::currentCam));
	if (enabled) {
		outLineColorN = hover ? hoverOutLineColor : outLineColor;
		colorN = hover ? hoverColor : color;
	}
	else {
		outLineColorN = disabledOutLineColor;
		colorN = disabledColor;
	}


	if (Mouse::leftClickPressed) {
		pressed = hover;
		if (pressed) {
			Mouse::leftClickPressed = false;
			if (enabled) {
				outLineColorN = pressedColor;
				colorN = pressedOutLineColor;
			}
		}
	}
	if (icon) {
		icon->transform.position = transform.position - (icon->size - size) / 2;
		if (icon->name == "text") {
			auto ic = static_cast<TextUI*>(icon);
			if (!enabled) {
				ic->color = Color(155);
			}
			else {
				ic->color = Color(255);
			}
		}
	}
}
void ButtonUI::Draw() {
	FigureDrawer::DrawFillRect(body + transform.position, colorN, false);
	FigureDrawer::DrawRect(body + transform.position, outLineColorN, false);
}

void ButtonUI::SetActive(bool b) {
	if (icon)
		icon->SetActive(b);
	UIComponentGO::SetActive(b);
}