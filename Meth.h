#pragma once

#include <cmath>
#include <math.h>
#include <iostream>
#include <stdlib.h> 
#include "Vector2.h"
static class Meth
{
public:
	static const double PI;
	static float Clamp(float _v, float _a, float _b);
	static double RadToDeg(double _n);
	static float DegToRad(float _n);
	static bool CrossLines(Vector2 l1p1, Vector2 l1p2, Vector2 l2p1, Vector2 l2p2);
	static float GetRandomRadAngle();
	static float AngleBetween(Vector2 v1, Vector2 v2, bool pi2 = false);
	static float SegToFrame(float s);
	static float FrameToSeg(int f);
};


