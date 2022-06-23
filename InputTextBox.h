#pragma once
#include "SizeInfoGO.h"
#include "Keyboard.h"
#include "Rect.h"
#include "FigureDrawer.h"
#include "Mouse.h"
#include "ColliderManager.h"
#include "Keyboard.h"
#include "TextDrawer.h"
#include "TextBox.h"

struct InputTextBox : public UIComponentGO
{
	bool hasMadeChange;
	std::string text;
	BoxCollider collider;
	Rect body;
	InputTextBox();
	void Set(Vector2 p, Rect b);
	void Update();
	void Draw();
	Color outLineColor;
	Color color;
	bool selected;
	TextBox tb;
	void UpdateText(std::string t);
	void Clear();
};
