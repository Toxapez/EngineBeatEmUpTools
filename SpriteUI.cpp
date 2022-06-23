#include "SpriteUI.h"

SpriteUI::SpriteUI() {
	layer = 10;
}

void SpriteUI::Set(Vector2 p, Rect b) {
	transform.position = p;
	body = b;
	size = Vector2(body.w, body.h);
}

void SpriteUI::Draw() {
	texture->Draw(transform.position + size/2);
}