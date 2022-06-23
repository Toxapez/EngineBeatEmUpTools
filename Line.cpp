#include "Line.h"

Line::Line(){
}

Line::Line(Vector2 p1, Vector2 p2) {
	points = std::pair(p1,p2);
}

bool Line::operator*(Line other) {
	if (SideToSide(other)) {
		return other.SideToSide(*this);
	}
	return false;
}

bool Line::SideToSide(Line other) {
	Vector2 offsetPos = points.first * -1;

	Line l = Line(other.points.first + offsetPos, other.points.second + offsetPos);

	float offsetAngle = -(points.second + offsetPos).GetAngle();
	float f1Angle = l.points.first.GetAngle() + offsetAngle;
	float f2Angle = l.points.second.GetAngle() + offsetAngle;

	l.points.first = Vector2::VectorFromAngle(l.points.first.Magnitude(), f1Angle);
	l.points.second = Vector2::VectorFromAngle(l.points.second.Magnitude(), f2Angle);


	
	if (l.points.first.y < 0 && l.points.second.y > 0) {
		return true;
	}

	return l.points.second.y < 0 && l.points.first.y > 0;
}

bool Line::CrossLinePoint(Line l1, Line l2, Vector2* vr){
	bool r = false;
	if (l2.SideToSide(l1)) {
		Vector2 offsetPos = l1.points.first * -1;

		Line l = Line(l2.points.first + offsetPos, l2.points.second + offsetPos);

		float offsetAngle = -(l1.points.second + offsetPos).GetAngle();
		float f1Angle = l.points.first.GetAngle() + offsetAngle;
		float f2Angle = l.points.second.GetAngle() + offsetAngle;

		l.points.first = Vector2::VectorFromAngle(l.points.first.Magnitude(), f1Angle);
		l.points.second = Vector2::VectorFromAngle(l.points.second.Magnitude(), f2Angle);



		if (l.points.first.y < 0 && l.points.second.y > 0) {
			r = true;
		}else r =  l.points.second.y < 0 && l.points.first.y > 0;

		if (r) {
			Vector2 nv = l.points.second - l.points.first;
			double alpha = nv.GetAngle();
			float ca = l.points.first.y * -1;
			double co = ca / tan(alpha);
			Vector2 rpos = Vector2(co + l.points.first.x,0);
			rpos = rpos.Rotate(-offsetAngle);
			*vr = rpos - offsetPos;

			//Vector2 nv = l.points.second - l.points.first;
			//double alpha = nv.GetAngle();
			//float ca = l.points.first.y * -1;
			//double co = ca / atan(alpha);
			//double size = co + l.points.first.x;
			//Vector2 originalL1 = (l1.points.second - l1.points.first);
			//*vr = (originalL1 * (size / originalL1.Magnitude())) + l1.points.first;
		}
	}
	return r;
}