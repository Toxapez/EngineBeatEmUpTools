#pragma once
#include "SizeInfoGO.h"
#include "Mouse.h"
#include "ColliderManager.h"
#include "TextUI.h"
struct ButtonUI : public UIComponentGO
{
	UIComponentGO* icon;
	bool pressed;
	BoxCollider collider;
	Rect body;
	ButtonUI();
	void Set(Vector2 p, Rect b);
	void Update();
	void Draw();
	bool enabled;
	Color outLineColor;
	Color color;
	Color hoverOutLineColor;
	Color hoverColor;
	Color pressedOutLineColor;
	Color pressedColor;
	Color disabledOutLineColor;
	Color disabledColor;
	void SetActive(bool b);
private:
	Color outLineColorN;
	Color colorN;
};

