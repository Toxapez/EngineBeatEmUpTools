#include "RectFourPoint.h"

RectFourPoint::RectFourPoint() {
	points[0] = Vector2();
	points[1] = Vector2();
	points[2] = Vector2();
	points[3] = Vector2();
}

RectFourPoint::RectFourPoint(Vector2 p1, Vector2 p2) {
	points[0] = p1;
	points[1] = Vector2(p2.x, p1.y);
	points[2] = Vector2(p1.x, p2.y);
	points[3] = p2;
}

void RectFourPoint::GetLines(Line* l) {
	l[0] = Line(points[0],points[1]);
	l[1] = Line(points[0], points[2]);
	l[2] = Line(points[3], points[1]);
	l[3] = Line(points[3], points[2]);
}

RectFourPoint RectFourPoint::Rotate(float angle, Vector2 ref) {
	RectFourPoint r = *this;
	for (int i = 0; i < 4; i++) {
		r.points[i] -= ref;
		r.points[i] = r.points[i].Rotate(angle);
		r.points[i] += ref;
	}
	return r;
}

Vector2 RectFourPoint::GetCenter() {
	return (points[3] - points[0]) / 2;
}