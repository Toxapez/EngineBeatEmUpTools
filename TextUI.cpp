#include "TextUI.h"


TextUI::TextUI() {
	layer = 10;
	name = "text";
}

void TextUI::Set(Vector2 p, Rect b) {
	body = b;
	transform.position = p;
	tb = TextBox(Vector2(), body);
	size = Vector2(body.w, body.h);
}

void TextUI::Update() {
}
void TextUI::Draw() {
	tb.pos = transform.position + size / 2;
	tb.displayText = Text(text, 15, color, "arial", false);
	tb.Draw();
}