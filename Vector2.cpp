#include "Vector2.h"
const double Vector2::PI = std::acos(-1);

Vector2::Vector2() {
	x = 0;
	y = 0;
}
Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}
Vector2 Vector2::operator+(Vector2 _v) {
	return Vector2(x + _v.x, y + _v.y);
}
Vector2 Vector2::operator-(Vector2 _v) {
	return Vector2(x - _v.x, y - _v.y);
}
Vector2 Vector2::operator*(float _i) {
	return Vector2(x * _i, y * _i);
}
float Vector2::operator*(Vector2 _v) {
	return (_v.x * x) + (_v.y * y);
}
Vector2 Vector2::operator/(float _i) {
	return Vector2(x / _i, y / _i);
}
void Vector2::operator-=(Vector2 _v) {
	x -= _v.x;
	y -= _v.y;
}
void Vector2::operator+=(Vector2 _v) {
	x += _v.x;
	y += _v.y;
}

void Vector2::operator*=(float _i) {
	x *= _i;
	y *= _i;
}
void Vector2::operator/=(float _i) {
	x /= _i;
	y /= _i;
}

bool Vector2::operator==(Vector2 _v) {
	return x == _v.x && y == _v.y;
}
bool Vector2::operator!=(Vector2 _v) {
	return !(x == _v.x && y == _v.y);
}

float Vector2::Magnitude() {
	return abs(sqrt(pow(x, 2) + pow(y, 2)));
}

Vector2 Vector2::Normalize() {
	if (*this == Vector2())
		return *this;
	return *this / this->Magnitude();
}

Vector2 Vector2::Rotate(float grados) {
	return Vector2(x * cos(grados) - y * sin(grados), x * sin(grados) + y * cos(grados));
}

Vector2 Vector2::RotateRef(float grados, Vector2 ref) {
	return ((*this - ref).Rotate(grados))+ref;
}

float Vector2::GetAngle(bool pi2) {
	double angle = atan2(y, x);
	if (pi2) {
		if (angle < 0) { angle += 2 * PI; }
		return 2 * PI - angle;
	}
	return angle;
}



Vector2 Vector2::VectorFromAngle(float h, float angle) {
	return Vector2(cos(angle) * h ,sin(angle)*h);
}