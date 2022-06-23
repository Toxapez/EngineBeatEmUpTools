#pragma once
#include "SizeInfoGO.h"
#include "Mouse.h"
#include "ColliderManager.h"
#include "SpriteStatic.h"

struct BoxCatcherUI : public UIComponentGO
{
	SpriteStatic* texture;
	bool pressed;
	BoxCollider collider;
	Rect body;
	Vector2 offset;
	BoxCatcherUI();
	void Set(Vector2 p, Rect b);
	void Update();
	void Draw();
	bool enabled;
	Vector2 firstPos;
	Vector2 secondPos;
	Rect boxCatched;
	bool hasMadeChange;
	int mode;
	void Clear();
};

