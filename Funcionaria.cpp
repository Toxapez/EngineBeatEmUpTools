#include "Funcionaria.h"

Scoper50<Funcionaria> Funcionaria::placerScope;
Animation  
Funcionaria::idleAnimS,
Funcionaria::runAnimS,
Funcionaria::damagedAnimS,
Funcionaria::deadAnimS,
Funcionaria::attackAnimS;
Funcionaria::Funcionaria() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	damagedAnim = &damagedAnimS;
	deadAnim = &deadAnimS;
	attackAnim = &attackAnimS;
	currentAnim = *idleAnim;
	attackDelay = 100;
	attackRadius = 550;
	fleeRadius = 470;
	name = "senora";
}


void Funcionaria::CalculateFacingSide() {
	float offsetFlip = speed.Get() * .6;
	if (movement.x < -offsetFlip)
		facingside = false;
	else if (movement.x > offsetFlip)
		facingside = true;
}

void Funcionaria::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (idleAnimS.dir == "") {
		idleAnimS.Set("funcionaria/idle");
		runAnimS.Set("funcionaria/run");
		runAnimS.loop = true;
		damagedAnimS.Set("funcionaria/damaged");
		deadAnimS.Set("funcionaria/dead");
		attackAnimS.Set("funcionaria/attack");
		int f1[] = { 0,1 };
		int f2[] = { 3,1 };
		attackAnimS.ModifyTimeline(f1, f2, 2);
	}
}

void Funcionaria::Movement() {
	movement = Vector2();
	vDistance = objective->transform.position - transform.position;
	distance = vDistance.Magnitude();
	dir = vDistance.Normalize();
	if (state == "running" ) {
		movement = dir  * speed.Get() * Kang::gameTimeSpeed ;

	}else if(state == "fleeing") {
		movement = (dir*-1) * speed.Get() * Kang::gameTimeSpeed;
	}
}

void Funcionaria::Animator() {
	if (state == "attacking") {}
	else if (distance <= fleeRadius) {
		if (state != "fleeing") {
			state = "fleeing";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}
	else if (distance <= attackRadius && attackDelayCounter <= 0) {
		if (state != "attacking") {
			Vector2 dirplayer = Player::player.transform.position - transform.position;
			facingside = dirplayer.x > 0;
			state = "attacking";
			currentAnim = *attackAnim;
			currentAnim.Reset();
			attackDelayCounter = attackDelay;
			bolsaHasBeenThrow = false;
			Audio::instance.voice.Play(name + "/ataca");
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
		if (currentAnim.framesPlayed == 3 && !bolsaHasBeenThrow) {
			bolsaHasBeenThrow = true;
			Bala::scoper.GetNextScope().Set("bolsa1", transform.position,( Player::player.transform.position - transform.position).Normalize() * 6,damage.Get());
		}
		if (currentAnim.HasEnded())
			state = "idle";
	}
	else if (state == "fleeing") {}
	else if (state == "running") {}
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}

PlaceableObject* Funcionaria::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	damageColorCounter = 0;
	squashGolpe = 0;
	LevelState::instance.nEnemies++;
	vibrationCounter = 0;

	Being::Reset(this, 10, 7, 15);
    
	return this;
}


PlaceableObject* Funcionaria::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Funcionaria::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Funcionaria::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}