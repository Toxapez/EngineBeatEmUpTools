#pragma once
#include "WindowUIComponent.h"
#include "FigureDrawer.h"
#include "Mouse.h"
#include "ColliderManager.h"

struct WindowUI : public GameObject
{
	std::vector<WindowUIComponent*> components;
	WindowUI();
	void Update();
	void Draw();
	Vector2 size;
	Vector2 frameOffSet;
	Color frameColor;
	Color bodyColor;
	void AddComponent(WindowUIComponent* c);
	void SetActive(bool b);
	BoxCollider collider;
};
