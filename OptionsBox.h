#pragma once
#include "TextBox.h"
#include <vector>
#include "ColliderManager.h"
#include "Console.h"
struct OptionsBox {
	Vector2 optionsCellSize;
	TextBox title;
	std::vector<TextBox> options;
	OptionsBox(){}
	OptionsBox(Vector2* refPos, std::string name, Vector2 s, std::vector<std::string> names, Vector2 originPos = Vector2());
	void Draw();
	int CollidingWithPoint(Vector2 p);
	Color baseButtonColor;
	Vector2* refPos;
	Vector2 originPos;
};


