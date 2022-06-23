#include "Enemy.h"

Player* Enemy::objective = &Player::player;
AudioTracker Enemy::enemiesMouth;
std::vector<Enemy*> Enemy::currentEnemies;

Enemy::Enemy() {
	//collider
	Vector2 spriteSize = Vector2(355, 200);
	spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	bodyCollider.layer = 3;
	Vector2 offset = Vector2(-10, 0);
	colliderSize = Vector2(60, 70);
	bodyCollider.Set(colliderSize * -.5 + offset, colliderSize + offset, this);
	triggerRadius = 4000;
	attackRadius = 40;
	attackColliderOffset = attackRadius;
	attackDelay = 60;
	stun = 20;
	
	attackCollider.Set(Vector2(), 60, this);
	//attackCollider.drawable = true;
	//bodyCollider.drawable = true;
	isActive = false;
	layer = 0;
	damageColor = Color(255, 170, 0);
	damageColorCounter = 0;
	talkingRange = 1000;

	pushCollider.Set(Vector2(0, 50), 30, this);
	pushCollider.layer = 5;
	spawnSquashCounterDecrease = .2;
}

void Enemy::LightUpdate() {
	isOnScreen = ScreenEffects::instance.IsOnScreen(transform.position);
	if (isOnScreen)
		Events::instance.enemiesOnScreen.happened = true;
	if(damageColorCounter > 0)
		damageColorCounter -= Kang::gameTimeSpeed;
	if (squashGolpe > 0) {
		squashGolpe -= Kang::gameTimeSpeed * .2;
	}
	if (spawnSquashCounter > 0) {
		spawnSquashCounter -= Kang::gameTimeSpeed * spawnSquashCounterDecrease;;
	}
	if (Keyboard::KeyboardCheck(SDL_SCANCODE_LALT)) {
		if (Keyboard::KeyboardPressed(SDL_SCANCODE_1)) {
			Damage(transform.position,100000);
		}
	}

	if (vibrationCounter > 0) {
		vibrationCounter += Kang::gameTimeSpeed;
		if (vibrationCounter >= 10) {
			vibration = Vector2(-5 + rand() % 10, -5 + rand() % 10);
			vibrationCounter -= 10;
		}
	}
}

void Enemy::CalculateFacingSide() {
	float offsetFlip = speed.Get() * .6;
	if (attackDelayCounter <= 0) {
		if (movement.x < -offsetFlip)
			facingside = false;
		else if (movement.x > offsetFlip)
			facingside = true;
	}
}

void Enemy::Update() {
	LightUpdate();
	Movement();
	if(minimunShutTimeCounter <= 0)
		if (distance < talkingRange)
			ChangeRandomTalking();
	CalculateFacingSide();
	Animator();
	NonMovementHandling();
	transform.position += movement;
	Collisions();
}

void Enemy::Collisions() {

	

	FalseAllCollidingSides();
	bool r = !facingside;
	InvisibleWall::CollisionsWithAllBlocks(r, &bodyCollider, &movement, sidesColliding);

	bool pushed = false;
	Vector2 prepushedPos = transform.position;
	if (!(sidesColliding[0] && sidesColliding[1] && sidesColliding[2] && sidesColliding[3])) {
		for (int i = 0; i < Collider::colliders.placerScope; i++) {
			auto c = Collider::colliders[i];
			if (*c->isActive) {
				if (c->layer == 5) {
					if (*c->gameObject != *(GameObject*)this) {
						auto cc = (CircleCollider*)c;
						if (ColliderManager::CollidingCircleCircle(cc, &pushCollider)) {
							transform.position += ((pushCollider.pos - cc->pos).Normalize() * (pushCollider.radio) *
								(1 - ((pushCollider.pos - cc->pos).Magnitude() / (pushCollider.radio + cc->radio)))) * .5;
							pushed = true;
							pushCollider.Update();
						}
					}
				}
			}
		}
	}
	if (pushed) {
		bodyCollider.Update();
		for (int i = 0; i < Collider::colliders.placerScope; i++) {
			auto c = Collider::colliders[i];
			if (*c->isActive) {
				if (c->layer == 0 || c->layer == 1) {
					if (ColliderManager::AlignedBoxBoxOverlaping(&bodyCollider, (BoxCollider*)c)) {
						transform.position = prepushedPos;
						break;
					}
				}
			}
		}
	}
}

void Enemy::AfterStaticStart() {
	if (rs.empty()) {
		for (auto& p : std::filesystem::directory_iterator("assets/audio/" + name + "/random")) {
			std::string dir = p.path().string();
			std::string dirname;
			while (true) {
				if (dir.back() == '.') {
					dir.pop_back();
					break;
				}
				dir.pop_back();
			}
			while (true) {
				if (dir.back() == '\\') {
					break;
				}
				dirname.push_back(dir.back());
				dir.pop_back();
			}
			dir.clear();
			while (!dirname.empty())
			{
				dir.push_back(dirname.back());
				dirname.pop_back();
			}
			rs.push_back(dir);
		}
		cargaAnim.Set("particulas/carga1");
		cargaAnim.SetFPS(4);
		cargaAnim.loop = true;
	}
}

void Enemy::ChangeRandomTalking() {
	if (!GlobalStaticVariables::hasEnemyRandomTalk) {
		int r = rand() % 10000;

		if (r < 10 * Kang::gameTimeSpeed) {
			if (enemiesMouth.TryToTrack(RandomTalking(), &Audio::instance.voice)) {
				GlobalStaticVariables::hasEnemyRandomTalk = true;
				SomeoneTalked();
				DialogUI::instance.StartPopUp(name);
			}
		}
	}
}

std::string Enemy::RandomTalking() {
	int r = rand() % rs.size();
	return name + "/random/" + rs[r];
}

void Enemy::FalseAllCollidingSides() {
	for (int i = 0; i < 4; i++) {
		sidesColliding[i] = false;
	}
}

void Enemy::Draw() {
	if (!currentAnim.frames.empty()) {
		SDL_Rect r;
		Vector2 spriteSize = Vector2(355, 200) * Cam::currentCam->zoom;
		RectTwoPoint spriteRect = currentAnim.spriteRects[currentAnim.GetRealFrameBeingPlayed()];
		Vector2 squash = Vector2(1,1);
		//squassgolpe
		if (squashGolpe > 1) 
			squash = Vector2(.5, 1.5);
		else if(squashGolpe > 0) 
			squash = Vector2(1.2, .8);
		
		//squash spawn
		spawnSquashCounterDecrease = .2;
		if (spawnSquashCounter > 1.5) 
			squash = Vector2(1.2, .3);
		else if (spawnSquashCounter  > 0) 
			squash = Vector2(.5, 1.5);
		r = ((Rect(Vector2(spriteRect.p1.x * squash.x, spriteRect.p1.y * squash.y), Vector2(spriteRect.p2.x * squash.x, spriteRect.p2.y * squash.y)) + transform.position) + vibration).ToSDLRect();
		SDL_Point p = { r.w / 2, r.h / 2 };
		Color c = damageColorCounter > 0 ? damageColor : Color();
		//SDL_SetTextureColorMod(currentAnim.it, c.r, c.g, c.b);
		FigureDrawer::DrawTexture(currentAnim.it, r,c, !facingside);
		//SDL_RenderCopyEx(SDLClass::renderer, currentAnim.it, NULL, &r, Meth::RadToDeg(Cam::currentCam->rotation), &p, facingside ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
		if(carga)
			FigureDrawer::DrawTexture(cargaAnim.it, r, Color(255),!facingside);
		
	}
}

void Enemy::Movement() {
	movement = Vector2();
	attackPoint = Vector2((facingside ? attackColliderOffset : -attackColliderOffset), 0);
	vDistance = objective->transform.position - (attackPoint + transform.position);
	distance = vDistance.Magnitude();
	dir = vDistance.Normalize();
	if (state == "running") {
		if (distance <= triggerRadius && distance >= attackRadius) {
			movement = dir * speed.Get() * Kang::gameTimeSpeed;

		}
	}
}

void Enemy::Damage(Vector2 pos, float d) {
	damageColorCounter =  10;
	squashGolpe = 2;
	Audio::instance.voice.Play(name + "/golpeado");
	carga = false;
	Cam::currentCam->StartSimpleVibration(Meth::SegToFrame(.35), 5);
	vibrationCounter = 100;
	Being::Damage(pos,d);
	Events::instance.punchEnemie.happened = true;
	
}

void Enemy::Dead() {
	Being::Dead();
	Audio::instance.voice.Play(name + "/muere");
	LevelState::instance.nEnemies--;
	isActive = false;
	exists = false;
	Cam::currentCam->StartSimpleVibration(Meth::SegToFrame(.45), 8);
	Particle::scoper.GetNextScope().Set("sangre1", transform.position);
	int r = rand() % 100;
	if (r < 15) {
		DropPool::DecideDrop("normalEnemy", transform.position);
	}
	r = rand() % 100;
	if (r < 35) {
		Recolectables::scoper.GetNextScope().Set("sangre",transform.position);
	}
}

void Enemy::Animator() {

	if (state == "attacking") {}
	else if (distance <= attackRadius && attackDelayCounter <= 0){
		if (state != "attacking") {
			state = "attacking";
			Audio::instance.voice.Play(name + "/ataca");
			currentAnim = *attackAnim;
			currentAnim.Reset();
			attackDelayCounter = attackDelay;
		}
	}
	else if (distance > attackRadius && attackDelayCounter <= 0) {
		if (state != "running") {
			state = "running";
			currentAnim = *runAnim;
			currentAnim.Reset();
		}
	}else state = "idle";

	if (state == "attacking") {
		if (currentAnim.framesPlayed - 1 == 0) {
			attackCollider.originalpos = attackPoint;
			if (ColliderManager::CollidingBoxCircle(&objective->bodyCollider, &attackCollider)) {
				//objective->Damage(damage, stun);
			}
		}
		if (currentAnim.HasEnded())
			state = "idle";
	}
	else if (state == "running") {}	
	else currentAnim = *idleAnim;
	currentAnim.Play(Kang::gameTimeSpeed);
}

void Enemy::NonMovementHandling() {
	if (attackDelayCounter > 0)
		attackDelayCounter -= Kang::gameTimeSpeed;
}

PlaceableObject* Enemy::Set(Vector2 pos, int ID) {
	return nullptr;
}


PlaceableObject* Enemy::GetPlaceableObject(bool force) {
	return nullptr;
}

bool Enemy::AllUsed() {
	return false;
}

void Enemy::DeactivateAll() {
}