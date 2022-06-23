#pragma once
#include "Enemy.h"
#include "Scoper.hpp"
#include "Bala.h"
class Funcionaria : public Enemy
{
	static Animation idleAnimS, runAnimS, damagedAnimS, deadAnimS, attackAnimS;
public:
	static Scoper50<Funcionaria> placerScope;
	Funcionaria();
	void AfterStaticStart();
	void Animator();
	float fleeRadius;
	bool bolsaHasBeenThrow;
	void Movement();
	void CalculateFacingSide();
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

