#pragma once
#include "SizeInfoGO.h"
#include "TextDrawer.h"
#include "TextBox.h"

struct TextUI : public UIComponentGO
{
	Rect body;
	std::string text;
	void Update();
	void Draw();
	Color color;
	TextBox tb;
	TextUI();
	void Set(Vector2 p, Rect b);
};
