#include "Meth.h"
const double Meth::PI = std::acos(-1);

float Meth::Clamp(float _v,float _a, float _b) {
	if (_v < _a) {
		_v = _a;
	}
	else if( _b < _v) {
		_v = _b;
	}
	return _v;
}

double Meth::RadToDeg(double _n) {
	return _n * (180 / PI);
}
float Meth::DegToRad(float _n) {
	return _n / (180 / PI);
}

float Meth::SegToFrame(float s) {
	return s * 60;
}

float Meth::FrameToSeg(int f) {
	return (float)f / 60;
}

float Meth::GetRandomRadAngle() {
	return (rand() % (int)(Meth::PI * 1000))/1000;
}

float Meth::AngleBetween(Vector2 v1, Vector2 v2, bool pi2) {
	double angle = v2.GetAngle() - v1.GetAngle();

	if (pi2) {
		if (angle < 0) { angle += 2 * PI; }
	}
	else {
		if (angle > PI) { angle -= 2 * PI; }
		else if (angle <= -PI) { angle += 2 * PI; }
	}
	return 2 * PI - angle;
}