#include "Tank.h"
Scoper50<Tank> Tank::placerScope;
Animation Tank::idleAnimS, Tank::runAnimS, Tank::damagedAnimS, Tank::deadAnimS, Tank::attackAnimS;
Animation  Tank::fuerzaAnim;

Tank::Tank() {
	idleAnim = &idleAnimS;
	runAnim = &runAnimS;
	runAnimS.loop = true;
	damagedAnim = &damagedAnimS;
	deadAnim = &deadAnimS;
	attackAnim = &attackAnimS;
	name = "tank";
	attackRadius = 180;
	attackColliderOffset = 60;
	attackDelay = 80;
}

void Tank::Update() {
	Enemy::Update();
}

void Tank::Draw() {
	if (!currentAnim.frames.empty()) {
		SDL_Rect r;
		Vector2 squash = Vector2(1, 1);
		//squassgolpe
		Vector2 offserPos;
		if (squashGolpe > 1) {
			squash = Vector2(.5, 1.5);
		}
		else if (squashGolpe > 0)
			squash = Vector2(1.2, .8);

		//squash spawn
		if (spawnSquashCounter > 1) {
			spawnSquashCounterDecrease = .1;
			offserPos = Vector2(0, ((spawnSquashCounter - 1) / 1) * -700);
			if (spawnSquashCounter <= 1.1 * Kang::gameTimeSpeed) {
				Cam::currentCam->StartDecreasingVibration(.85, 60);
			}
		}
		else if (spawnSquashCounter > 0) {
			spawnSquashCounterDecrease = .05;
			currentAnim = *attackAnim;
			currentAnim.Reset();
			
		}

		RectTwoPoint spriteRect = currentAnim.spriteRects[currentAnim.GetRealFrameBeingPlayed()];
		
 		r = ((Rect(Vector2(spriteRect.p1.x * squash.x, spriteRect.p1.y * squash.y), Vector2(spriteRect.p2.x * squash.x, spriteRect.p2.y * squash.y)) + (transform.position + offserPos)) + vibration).ToSDLRect();
		SDL_Point p = { r.w / 2, r.h / 2 };
		Color c = damageColorCounter > 0 ? damageColor : Color();
		//SDL_SetTextureColorMod(currentAnim.it, c.r, c.g, c.b);
		//SDL_RenderCopyEx(SDLClass::renderer, currentAnim.it, NULL, &r, Meth::RadToDeg(Cam::currentCam->rotation), &p, facingside ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
		FigureDrawer::DrawTexture(currentAnim.it, r, c, !facingside);
		if (carga)
			FigureDrawer::DrawTexture(cargaAnim.it, r, Color(255), !facingside);

	}
	if (fuerza) {
		fuerzaAnim.Play(Kang::gameTimeSpeed);

		SDL_Rect r;
		Vector2 spriteSize = Vector2(355, 200) * Cam::currentCam->zoom;
		RectTwoPoint spriteRect = RectTwoPoint(spriteSize *-.5, spriteSize);
		Vector2 squash = Vector2(1, 1);
		r = ((Rect(Vector2(spriteRect.p1.x * squash.x, spriteRect.p1.y * squash.y), Vector2(spriteRect.p2.x * squash.x, spriteRect.p2.y * squash.y)) + transform.position)  + (Vector2(130, 0) * (facingside ? 1 : -1) * Cam::currentCam->zoom)).ToSDLRect();
		SDL_Point p = { r.w / 2, r.h / 2 };
		if (fuerza)
			FigureDrawer::DrawTexture(fuerzaAnim.it, r, Color(255), !facingside);
	}
}

void Tank::AfterStaticStart() {
	Enemy::AfterStaticStart();
	if (idleAnimS.dir == "") {
		idleAnimS.Set("tank/idle");
		runAnimS.Set("tank/run");
		runAnimS.loop = true;
		damagedAnimS.Set("tank/damaged");
		deadAnimS.Set("tank/dead");
		attackAnimS.Set("tank/attack");
		int f1[] = { 0,1 };
		int f2[] = { 6,4 };
		attackAnimS.ModifyTimeline(f1, f2, 2);
		fuerzaAnim.Set("particulas/fuerza1");
		fuerzaAnim.loop = true;
	}
}


PlaceableObject* Tank::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	currentAnim = *idleAnim;
	state = "idle";
	damageColorCounter = 0;
	squashGolpe = 0;
	LevelState::instance.nEnemies++;
	vibrationCounter = 0;
	carga = false;
	fuerza = false;

	spawnSquashCounterDecrease = .1;
	Being::Reset(this, 40, 4, 15);

	return this;
}

void Tank::Animator() {

	if(spawnSquashCounter > 0){}
	else if (state == "attacking") {}
	else if (distance <= attackRadius && attackDelayCounter <= 0) {
		if (state != "attacking") {
			state = "attacking";
			currentAnim = *attackAnim;
			currentAnim.Reset();
			attackDelayCounter = attackDelay;
			Audio::instance.voice.Play(name + "/ataca");
			dirAttack = (Player::player.transform.position - transform.position).Normalize() * 40;
			facingside = dirAttack.x > 0;
			carga = true;
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
		if (currentAnim.GetRealFrameBeingPlayed() == 0) {
			cargaAnim.Play(Kang::gameTimeSpeed);
			movement -= dirAttack*.1;
			
		}
		else if (currentAnim.GetRealFrameBeingPlayed() == 1) {
			carga = false;
			fuerza = true;
			movement += dirAttack;
			dirAttack = dirAttack * .90;
			attackCollider.originalpos = attackPoint;
			if (ColliderManager::CollidingBoxCircle(&objective->bodyCollider, &attackCollider)) {
				objective->Damage(transform.position, damage.Get());
			}
		}
		if (currentAnim.HasEnded()) {
			state = "idle";
			fuerza = false;
		}
	}
	else if (state == "running") {}
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}

PlaceableObject* Tank::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Tank::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Tank::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}