#include "VieneViene.h"

Scoper50<VieneViene> 
           VieneViene::placerScope;
Animation  VieneViene::idleAnimS, 
		   VieneViene::runAnimS, 
		   VieneViene::damagedAnimS, 
	       VieneViene::deadAnimS, 
		   VieneViene::attackAnimS;
VieneViene::VieneViene() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	damagedAnim = &damagedAnimS;
	deadAnim = &deadAnimS;
	attackAnim = &attackAnimS;
	currentAnim = *idleAnim;
}
void VieneViene::AfterStaticStart() {

}

void VieneViene::Update() {
	Enemy::Update();
}

void VieneViene::Draw() {
	Enemy::Draw();

}

void VieneViene::SetAnimations() {
	idleAnimS.Set("vieneviene/idle");
	runAnimS.Set("vieneviene/run");
	runAnimS.loop = true;
	damagedAnimS.Set("vieneviene/damaged");
	deadAnimS.Set("vieneviene/dead");
	attackAnimS.Set("vieneviene/attack");
}

PlaceableObject* VieneViene::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	LevelState::instance.nEnemies++;
	return this;
}


PlaceableObject* VieneViene::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool VieneViene::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void VieneViene::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}