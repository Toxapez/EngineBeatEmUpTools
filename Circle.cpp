#include "Circle.h"

Circle::Circle() {
	radio = 1;
}

Circle::Circle(Vector2 p, float r) {
	pos = p;
	radio = r;
}

Rect Circle::ToRect() {
	return Rect(pos.x -radio,pos.y-radio,radio*2,radio*2);
}