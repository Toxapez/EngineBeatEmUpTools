#pragma once
#include "SizeInfoGO.h"
#include "Mouse.h"
#include "TextBox.h"
#include "ColliderManager.h"
#include "Rect.h"
#include "FigureDrawer.h"
#include "StringUtilities.h"

struct FileCatcher : public UIComponentGO
{
	TextBox tb;
	BoxCollider collider;
	void Update();
	void Draw();
	Rect body;
	FileCatcher();
	void Set(Vector2 p, Vector2 s);
	Text message;
	std::string dir;
	bool hasMadeChange;
	float deleteDelay;
	void Clear();
};
