#pragma once
#include "Enemy.h"
#include "Scoper.hpp"

class Guard : public Enemy
{
	static Animation idleAnimS, runAnimS, damagedAnimS, deadAnimS, attackAnimS;
public:
	static Scoper50<Guard> placerScope;
	Guard();
	void Update() override;
	void Draw() override;
	void AfterStaticStart();
	void Animator();
	void Damage(Vector2 pos, float d) override;
	void Dead();
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
	
};

