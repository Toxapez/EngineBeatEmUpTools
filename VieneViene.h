#pragma once
#include "Enemy.h"
#include "Scoper.hpp"
class VieneViene : public Enemy
{
	static Animation idleAnimS, runAnimS, damagedAnimS, deadAnimS, attackAnimS;
public:
	static Scoper50<VieneViene> placerScope;
	VieneViene();
	void Update() override;
	void Draw() override;
	static void SetAnimations();
	void AfterStaticStart();
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

