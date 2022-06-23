#include "Oficinista.h"

Scoper1000<Oficinista> Oficinista::placerScope;
Animation
Oficinista::runAnimS, Oficinista::idleAnimS;
Oficinista::Oficinista() {
	runAnim = &runAnimS;
	idleAnim = &idleAnimS;
	name = "oficinista";
}

void Oficinista::Update() {
	LightUpdate();

	
	if (!isOnScreen || !scared) {
		if (state != "idle") {
			state = "idle";
			currentAnim = *idleAnim;
			currentAnim.Reset();
		}
	}else{
		if (state != "running") {
			state = "running";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}


	currentAnim.Play(Kang::gameTimeSpeed);
	if (state == "idle") {
		if (Events::instance.throwObject.happen || Events::instance.punchEnemie.happen) {
			if (isOnScreen) {
				scared = true;
			}
		}
	}
	else if (state == "running") {
		movement = dir * speed.Get() * Kang::gameTimeSpeed;
		transform.position += movement;
	}
	vDistance = objective->transform.position - transform.position;
	distance = vDistance.Magnitude();
	if (minimunShutTimeCounter <= 0)
		if(distance < talkingRange)
			ChangeRandomTalking();
	Collisions();
	if (sidesColliding[0] || sidesColliding[3]) dir =      Vector2(dir.x,-dir.y);
	else if (sidesColliding[1] || sidesColliding[2]) dir = Vector2(-dir.x, dir.y);
	
	
	
}

void Oficinista::Damage(Vector2 pos, float d) {
	Enemy::Damage(pos,d);
	dir = (transform.position - pos).Normalize();
	ScareAllOnScreen();
}

void Oficinista::ScareAllOnScreen() {
	for (int i = 0; i < placerScope.maxEntities; i++)
	{
		if (placerScope[i].isActive) {
			if (ScreenEffects::instance.IsOnScreen(placerScope[i].transform.position)) {
				placerScope[i].scared = true;
			}
		}
	} 
}

void Oficinista::Draw() {
	Enemy::Draw();

}


void Oficinista::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (runAnimS.dir == "") {
		runAnimS.Set("oficinista/run");
		runAnimS.loop = true;
		idleAnimS.Set("oficinista/idle");
	}
}

PlaceableObject* Oficinista::Set(Vector2 pos, int ID) {
	damageColorCounter = 0;
	transform.position = pos;
	isActive = true;
	currentAnim = *runAnim;
	state = "running";
	dir = Vector2::VectorFromAngle(1,Meth::GetRandomRadAngle());
	squashGolpe = 0;
	LevelState::instance.nEnemies++;
	vibrationCounter = 0;
	scared = false;

	Being::Reset(this, 3, 5, 10);

	return this;
}



PlaceableObject* Oficinista::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Oficinista::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Oficinista::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}