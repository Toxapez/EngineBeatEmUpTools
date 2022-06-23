#include "ScreenEffects.h"

ScreenEffects ScreenEffects::instance;

ScreenEffects::ScreenEffects() {
	layer = 1;
}

void ScreenEffects::Update() {
}

void ScreenEffects::Draw() {
	if (colorBlendCounter) {
		colorBlendCounter -= Kang::gameTimeSpeed;
		FigureDrawer::DrawFillRect(Rect(SDLClass::GetScreenSizeVector2()), Color(colorBlend.r, colorBlend.g, colorBlend.b,colorBlendCounter/maxBlend * 255 * blend), false);
	}
}

void ScreenEffects::Blend(float t, float b, Color c) {
	colorBlend = c;
	colorBlendCounter = t;
	maxBlend = t;
	blend = b;
}

bool ScreenEffects::IsOnScreen(Vector2 pos) {
	pos -= Cam::currentCam->transform.position;
	Vector2 centerCam = Cam::currentCam->transform.position;
	float fixedSize = 1.2;
	BoxCollider b = BoxCollider((SDLClass::GetScreenSizeVector2() / 2)*-fixedSize,SDLClass::GetScreenSizeVector2()/2 * fixedSize);
	return ColliderManager::CollidingBoxPoint(&b, pos);
}