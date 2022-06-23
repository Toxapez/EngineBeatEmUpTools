#pragma once
#include "Enemy.h"
#include "Scoper.hpp"
#include "Recolectables.h"
class Dinerin : public Enemy
{
	static Animation idleAnimS, runAnimS;
public:
	static Scoper50<Dinerin> placerScope;
	Dinerin();
	void AfterStaticStart();
	void Animator();
	void CalculateFacingSide();
	void Movement();
	float fleeRadius;
	void Dead();
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

