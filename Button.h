#pragma once
#include "FigureDrawer.h"
#include "GameObject.h"
#include "ColliderManager.h"
#include "Mouse.h"
#include "Cam.h"
struct Button : public GameObject
{
	BoxCollider collider;
	Color cNormal;
	Color cHover;
	Color cPressed;
	Color cOutline;
	bool pressed;
	bool pressing;
	Button();
	void Update();
	void Draw();

	int state;
	Vector2  size;
	void ChangeSize(Vector2);
};

