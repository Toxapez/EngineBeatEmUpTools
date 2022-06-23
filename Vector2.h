#pragma once
#include <cmath>

class Vector2
{
	static const double PI;
public:
	float x;
	float y;
	Vector2();
	Vector2(float _x, float _y);
	Vector2 operator+(Vector2 _v);
	Vector2 operator-(Vector2 _v);
	Vector2 operator*(float _i);
	float operator*(Vector2 _v);
	Vector2 operator/(float _i);
	void operator+=(Vector2 _v);
	void operator-=(Vector2 _v);
	void operator*=(float _v);
	void operator/=(float _v);

	bool operator==(Vector2 _v);
	bool operator!=(Vector2 _v);

	float Magnitude();
	Vector2 Normalize();
	Vector2 Rotate(float grados);
	Vector2 RotateRef(float grados, Vector2 ref);
	float GetAngle(bool pi2 = false);
	static Vector2 VectorFromAngle(float h, float angle);
	
};
