#pragma once
#include "Enemy.h"
#include "Scoper.hpp"
#include "Bala.h"
class Empleado : public Enemy
{
	static Animation idleAnimS, runAnimS, attackAnimS;
public:
	static Scoper50<Empleado> placerScope;
	Empleado();
	void AfterStaticStart();
	void Animator();
	bool paperBeenThrow;
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

