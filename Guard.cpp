#include "Guard.h"
Scoper50<Guard> Guard::placerScope;
Animation Guard::idleAnimS, Guard::runAnimS, Guard::damagedAnimS, Guard::deadAnimS, Guard::attackAnimS;
Guard::Guard() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	damagedAnim = &damagedAnimS;
	deadAnim = &deadAnimS;
	attackAnim = &attackAnimS;
	currentAnim = *idleAnim;
	attackDelay = 100;
	name = "guard";


	
}

void Guard::Update() {
	Enemy::Update();
}

void Guard::Draw() {
	Enemy::Draw();
}

void Guard::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (idleAnimS.dir == "") {
		idleAnimS.Set("guard/idle");
		runAnimS.Set("guard/run");
		runAnimS.SetFPS(3);
		runAnimS.loop = true;
		damagedAnimS.Set("guard/damaged");
		deadAnimS.Set("guard/dead");
		attackAnimS.Set("guard/attack");
		int f1[] = { 0,1,0,1,0,1 };
		int f2[] = { 5,1,1,1,1,1 };
		attackAnimS.ModifyTimeline(f1, f2, 6);
		
	}
}




void Guard::Animator() {

	if (state == "attacking") {}
	else if (distance <= attackRadius && attackDelayCounter <= 0) {
		if (state != "attacking") {
			state = "attacking";
			currentAnim = *attackAnim;
			currentAnim.Reset();
			attackDelayCounter = attackDelay;
			Audio::instance.voice.Play(name +"/ataca");
			carga = true;
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
		if (currentAnim.GetRealFrameBeingPlayed() == 0) {
			cargaAnim.Play(Kang::gameTimeSpeed);

		}
		else if (currentAnim.GetRealFrameBeingPlayed() == 1) {
			attackCollider.originalpos = attackPoint;
			carga = false;
			if (ColliderManager::CollidingBoxCircle(&objective->bodyCollider, &attackCollider)) {
				objective->Damage(transform.position, damage.Get());
			}
		}
		if (currentAnim.HasEnded())
			state = "idle";
	}
	else if (state == "running") {}
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}




void Guard::Damage(Vector2 pos, float d) {
	Enemy::Damage(pos,d);
	state = "idle";
}

void Guard::Dead() {
	Enemy::Dead();
	
}

PlaceableObject* Guard::Set(Vector2 pos, int ID) {
	transform.position = pos;
	damageColorCounter = 0;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	squashGolpe = 0;
	LevelState::instance.nEnemies++;
	carga = false;
	vibrationCounter = 0;

	Being::Reset(this, 10, 6, 5);

	return this;
}


PlaceableObject* Guard::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Guard::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Guard::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}