#include "Dinerin.h"

Scoper50<Dinerin> Dinerin::placerScope;
Animation Dinerin::idleAnimS, Dinerin::runAnimS;

Dinerin::Dinerin() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	fleeRadius = 1100;
	fleeRadius = 1150;
	name = "dinerin";
}

void Dinerin::CalculateFacingSide() {
	float offsetFlip = speed.Get() * .6;
	if (movement.x < -offsetFlip)
		facingside = true;
	else if (movement.x > offsetFlip)
		facingside = false;
}

void Dinerin::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (idleAnimS.dir == "") {
		idleAnimS.Set("dinerin/idle");
		runAnimS.Set("dinerin/run");
		runAnimS.loop = true;
	}
}

void Dinerin::Movement() {
	movement = Vector2();
	vDistance = objective->transform.position - transform.position;
	distance = vDistance.Magnitude();
	dir = vDistance.Normalize();
	if (state == "running") 
		movement = dir * speed.Get() * Kang::gameTimeSpeed;
	else if (state == "fleeing") {
		movement = (dir * -1) * speed.Get() * Kang::gameTimeSpeed;
	}
}


void Dinerin::Animator() {

	
	if(distance <= fleeRadius) {
		if (state != "fleeing") {
			state = "fleeing";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}
	else if (distance > attackRadius) {
		if (state != "running") {
			state = "running";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}
	else state = "idle";

	if (state == "attacking") {
		if (currentAnim.GetRealFrameBeingPlayed() == 1) {
		}
		if (currentAnim.HasEnded())
			state = "idle";
	}
	else if (state == "fleeing") {}
	else if (state == "running") {}
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}

void Dinerin::Dead() {
	Enemy::Dead();
	Recolectables::scoper.GetNextScope().Set("dinero",transform.position);

}

PlaceableObject* Dinerin::Set(Vector2 pos, int ID) {
	LevelState::instance.nEnemies++;
	transform.position = pos;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	damageColorCounter = 0;
	squashGolpe = 0;
	vibrationCounter = 0;

	Being::Reset(this, 2, 5);
	return this;
}



PlaceableObject* Dinerin::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Dinerin::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Dinerin::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}