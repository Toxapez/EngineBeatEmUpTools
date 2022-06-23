#pragma once
#include "Scoper.hpp"
#include "Vector2.h"
#include "FigureDrawer.h"
#include "GameObject.h"
struct Collider
{
	int layer;
	static Scoper100000<Collider*> colliders;
	bool* isActive;
	int type;
	bool drawable;
	Vector2* refPos;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	GameObject* gameObject;
	bool camDependetDrawing = false;
	Collider();
	static void AllUpdate();
	static void AllDraw();
};


