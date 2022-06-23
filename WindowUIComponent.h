#pragma once
#include "SizeInfoGO.h"

struct WindowUIComponent : UIComponentGO
{
	std::vector<UIComponentGO*> parts;
	void AddPart(UIComponentGO* p);
	void UpdatePos(Vector2 os);
	void LastUpdatePos(Vector2 p);
	void SetActive(bool b);
};

