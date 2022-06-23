#pragma once
#include "Enemy.h"
#include "Scoper.hpp"
class Oficinista : public Enemy
{
	static Animation runAnimS, idleAnimS;
public:
	static Scoper1000<Oficinista> placerScope;
	Oficinista();
	void Damage(Vector2 pos, float d) override;
	void Update() override;
	void Draw() override;
	void AfterStaticStart();
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
	bool scared;
	void ScareAllOnScreen();
};


