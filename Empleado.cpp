#include "Empleado.h"

Scoper50<Empleado> Empleado::placerScope;
Animation Empleado::idleAnimS, Empleado::runAnimS, Empleado::attackAnimS;

Empleado::Empleado() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	attackAnim = &attackAnimS;
	name = "empleado";

}


void Empleado::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (idleAnimS.dir == "") {
		idleAnimS.Set("empleado/idle");
		runAnimS.Set("empleado/run");
		runAnimS.loop = true;
		attackAnimS.Set("empleado/attack");
		int f1[] = { 0,1 };
		int f2[] = { 3,2 };
		attackAnimS.ModifyTimeline(f1, f2, 2);
	}
}


void Empleado::Animator() {

	if (state == "attacking") {}
	else if (distance <= attackRadius && attackDelayCounter <= 0) {
		if (state != "attacking") {
			state = "attacking";
			currentAnim = *attackAnim;
			currentAnim.Reset();
			attackDelayCounter = attackDelay;
			paperBeenThrow = false;
			Audio::instance.voice.Play(name + "/ataca");
		}
	}
	else if (distance > attackRadius && attackDelayCounter <= 0) {
		if (state != "running") {
			state = "running";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}
	else state = "idle";

	if (state == "attacking") {
		if (currentAnim.GetRealFrameBeingPlayed() == 1 && !paperBeenThrow) {
			paperBeenThrow = true;
			Bala::scoper.GetNextScope().Set("papeles1", transform.position + Vector2(150 * (facingside ? 1 : -1),0), Vector2(), damage.Get());
		}
		if (currentAnim.HasEnded())
			state = "idle";
	}
	else if (state == "running") {}
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}

PlaceableObject* Empleado::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	damageColorCounter = 0;
	squashGolpe = 0;
	LevelState::instance.nEnemies++;
	vibrationCounter = 0;

	Being::Reset(this, 15, 7, 5);
	return this;
}


PlaceableObject* Empleado::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Empleado::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Empleado::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}