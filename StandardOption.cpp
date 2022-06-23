#include "StandardOption.h"

StandardOption::StandardOption() {
	refPos = nullptr;
	alineo = ALIN_CENTERED;
	rectColor = Color(255);
}

StandardOption::StandardOption(Rect r, Text t) {
	containerRect = r;
	markRect = r;
	displayText = t;
	refPos = nullptr;
	alineo = ALIN_CENTERED;
}

void StandardOption::Draw(bool highlighted) {
	bgColor = highlighted ? Color(205) : Color(25);
	displayText.color = highlighted ? Color(0) : Color(255);
	TextBox::Draw();
}

bool StandardOption::isColliding(Vector2 v) {
	auto b = BoxCollider(Vector2(markRect.x, markRect.y), Vector2(markRect.w, markRect.h) + Vector2(markRect.x, markRect.y));
	return ColliderManager::CollidingBoxPoint(&b, v);
}