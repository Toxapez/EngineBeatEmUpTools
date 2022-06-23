#pragma once
#include "SizeInfoGO.h"

struct UIBar : public UIComponentGO
{
	std::vector<UIComponentGO*> parts;
	void AddPart(UIComponentGO* p);
	void UpdatePos(Vector2 os);
	void Update();
	void SetActive(bool b);
};

