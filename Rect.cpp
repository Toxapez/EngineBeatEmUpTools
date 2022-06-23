#include "Rect.h"

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(float X, float Y, float W, float H) {
	x = X;
	y = Y;
	w = W;
	h = H;
}

Rect::Rect(float W, float H) {
	x = 0;
	y = 0;
	w = W;
	h = H;
}

Rect::Rect(Vector2 v) {
	x = 0;
	y = 0;
	w = v.x;
	h = v.y;
}
Rect::Rect(Vector2 v1, Vector2 v2) {
	x = v1.x;
	y = v1.y;
	w = v2.x;
	h = v2.y;
}

SDL_Rect Rect::ToSDLRect() {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void Rect::Pos(Vector2 pos) {
	x = pos.x;
	y = pos.y;
}

Rect Rect::operator+(Vector2 other) {
	return Rect(x+other.x,y+other.y,w,h);
}

Rect Rect::operator-(Vector2 other) {
	return Rect(x - other.x, y - other.y, w, h);
}

bool Rect::operator==(Rect other) {
	return x == other.x && y == other.x && w == other.w && h == other.h;
}

bool Rect::operator!=(Rect other) {
	return !(*this == other);
}

Vector2 Rect::GetCenter() {
	return Vector2(x+w/2,y+h/2);
}

Rect Rect::GetRectFromCenter(Vector2 pos, Vector2 size) {
	Rect r;
	r.x = pos.x - size.x / 2;
	r.y = pos.y - size.y / 2;
	r.w = size.x;
	r.h = size.y;
	return r;
}