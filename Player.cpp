#include "Player.h"

Player Player::player;

Player::Player() {
	

	currentAnim = &idleAnim;
	//collider
	Vector2 spriteSize = Vector2(355 , 200);
	spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	colliderSize = Vector2(70, 70);
	Vector2 colliderOffset = Vector2(0,50);
	bodyCollider.Set(colliderSize * -.5 + colliderOffset, colliderSize * .5 + colliderOffset, this);
	//bodyCollider.drawable = true;
	collider = &bodyCollider;
	Vector2 acSize = Vector2(120, 160);
	Vector2 acoffset = Vector2(0,40);
	attackCollider.Set(acSize * -.5 + acoffset, acSize * .5 + acoffset, this);
	//attackCollider.drawable = true;
	//cam
	cam.SetCamMovible(Vector2(),1);
	cam.isActive = true;

	//normal init
	placeableObject = true;

	//dash
	dashDistance = 300;
	dashSpeed = 20;
	isActive = false;

	layer = 0;

	//acuaticSound = Audio::instance.sfx.SetAudio("pm/acuatico",true);
	inmuneTime = Meth::SegToFrame(.5);


	
}

void Player::AfterStaticStart() {
	//Animations
	idleAnim.Set("pinchim/idle");
	idleAnim.loop = true;

	runAnim.Set("pinchim/run");
	runAnim.loop = true;

	dashAnim.Set("pinchim/dash");
	dashAnim.loop = true;

	blockAnim.Set("pinchim/block");

	damagedAnim.Set("pinchim/damaged");

	attack1Anim.Set("pinchim/attack1");

	attack2Anim.Set("pinchim/attack2");

	attack3Anim.Set("pinchim/attack3");

	attack4Anim.Set("pinchim/attack4");

	deadAnim.Set("pinchim/dead");

	pistola.Set("pinchim/pistola");

	playerHitCollider = &bodyCollider;

	Audio::instance.music.Play("bgmusic/banco1", true);
}

void Player::Update() {

	if (PlayerVariables::instance.liquid > 200)
		PlayerVariables::instance.liquid = 200;

	isOnScreen = ScreenEffects::instance.IsOnScreen(transform.position);

	if (!Events::instance.enemiesOnScreen.happen) {
		if (LevelState::instance.nEnemies > 0) {
			float nearest = 9999;
			Vector2* nearestV = nullptr;
			for (auto c : activeBeings) {
				if (c->gameObject->isActive) {
					if (!c->isOnScreen) {
						float dist = (transform.position - c->gameObject->transform.position).Magnitude();
						if (dist < nearest) {
							nearestV = &c->gameObject->transform.position;
							nearest = dist;
						}
						
					}
				}
			}
			poitingArrowDir = nearestV;
		}
	}
	else poitingArrowDir = nullptr;

	if (PlayerVariables::instance.handObject.name != "") {
		if (InputManager::item) {
			if (PlayerVariables::instance.handObject.name == "lesheShabo") {
				if (PlayerVariables::instance.handObject.nSS == 0) {
					speed.SetTemporal(7,Meth::SegToFrame(5));
				}
				else if (PlayerVariables::instance.handObject.nSS == 1) {
					Heal(20);
				}
				else if (PlayerVariables::instance.handObject.nSS == 2) {
					speed.SetTemporal(4, Meth::SegToFrame(5));
					damage.SetTemporal(1, Meth::SegToFrame(5));
					fuerza.SetTemporal(2, Meth::SegToFrame(5));
				}
				else if (PlayerVariables::instance.handObject.nSS == 3) {
					for (auto c : Being::activeBeings) {
						if (c->gameObject->isActive)
							c->damage.SetTemporal(4, Meth::SegToFrame(5));
					}
				}
				else if (PlayerVariables::instance.handObject.nSS == 4) {
					damage.SetTemporal(2, Meth::SegToFrame(5));
				}
				else if (PlayerVariables::instance.handObject.nSS == 5) {
					fuerza.SetTemporal(4, Meth::SegToFrame(5));
				}
				else if (PlayerVariables::instance.handObject.nSS == 6) {
					for (auto c : Being::activeBeings) {
						if (c->gameObject->isActive)
							if(c->isOnScreen)
								c->Damage(c->gameObject->transform.position, 20);
					}
				}
				PlayerVariables::instance.handObject.showRecolectableInfo = true;
				PlayerVariables::instance.handObject.name = "";
			}
		}
	}

	if (yellTime > 0)
		yellTime -= Kang::gameTimeSpeed;
	if (minimunShutTimeCounter > 0)
		minimunShutTimeCounter -= Kang::gameTimeSpeed;
	if(inmuneTimeCounter > 0)
		inmuneTimeCounter -= Kang::gameTimeSpeed;

	if (Kang::gameTimeSpeed > 0) {
		Movement();
		NonMovementInputHandling();

		Animator();
	}
	if (state == "running" || state == "acuatic") {
		movement = dir * (state == "running" ? speed.Get() : dashSpeed) * Kang::gameTimeSpeed;
		transform.position += movement;
	}
	else
	{
		movement = Vector2();
	}



	//spritefacing
	if (movement.x != 0)
		facingside = movement.x > 0;

	Collisions();

	cam.transform.position = transform.position;
}
void Player::Damage(Vector2 pos, float d) {
	if (state != "acuatic" && stunedCounter <= 0 && inmuneTimeCounter <= 0) {
		float gravedad;
		float seriusDamage = 30;
		if (d >= seriusDamage)
			gravedad = 1;
		else gravedad = d / seriusDamage;

		Being::Damage(pos, d);
		stunedCounter = 10;
		Audio::instance.sfx.Play("effect/hit");
		cam.StartSimpleVibration(Meth::SegToFrame(.2), gravedad * 10);
		vibrationCounter = gravedad * 20;
		ScreenEffects::instance.Blend(10,gravedad,Color(255,0,0));
		Cam::currentCam->StartSimpleZoomAnimation(.25 * gravedad,Meth::SegToFrame(.2));
		if (yellTime <= 0) {
			Audio::instance.voice.Play("pm/golpeado");
			yellTime = 22;
		}
	}
}

void Player::Dead() {
	Being::Dead();
	isActive = false;
	exists = false; 
}

void Player::Movement() {
	dir = Vector2();
	if (InputManager::up)
		dir += Vector2(0, -1);
	if (InputManager::down)
		dir += Vector2(0, 1);
	if (InputManager::left)
		dir += Vector2(-1, 0);
	if (InputManager::right)
		dir += Vector2(1, 0);
	dir = dir.Normalize();

	dirshoot = Vector2();
	if (InputManager::movup)
		dirshoot += Vector2(0, -1);
	else if (InputManager::movdown)
		dirshoot += Vector2(0, 1);
	else if (InputManager::movleft)
		dirshoot += Vector2(-1, 0);
	else if (InputManager::movright)
		dirshoot += Vector2(1, 0);
	dirshoot = dirshoot.Normalize();

	if (dirshoot.Magnitude() > 0) {
		shootDelayCounter += Kang::gameTimeSpeed;
		if (shootDelayCounter > 5) {
			shootDelayCounter -= 10;
			//BalaEstandar::scoper.GetNextScope().Set(transform.position,(dirshoot*60).Rotate((-5 +rand() % 10) * .03));
		}
	}
	
}

void Player::NonMovementInputHandling() {
	
	if (InputManager::dash) {
		dashing = true;
	}
	else {
		if (dashing) {
			dashing = false;
			//acuaticSound->setIsPaused(true);
			
		}
	}
	
	if (InputManager::attack && !dashing) {
		if (state != "attacking") {
			attacking = true;
		}
 		else if (scheduledAttacks < 1)
			scheduledAttacks++;
	}
}

void Player::Animator() {
	

	//startingAnimation
	if (DialogUI::instance.inDialog) {
		if (state != "inDialog") {
			state = "inDialog";
			currentAnim = &idleAnim;
		}
	}
	else if (stunedCounter > 0) {
		if (state != "stunning") {
			state = "stunning";
			currentAnim = &damagedAnim;
		}
	}
	else if (dashing) {
		if (state != "acuatic") {
			state = "acuatic";
			//acuaticSound->setIsPaused(false);
			Particle::scoper.GetNextScope().Set("acuatico1", transform.position,facingside);
			Audio::instance.sfx.Play("pm/acuatico", false);
		}
	}
	else if (attacking) {
		if (state != "attacking") {
			state = "attacking";
			AssingAttackAnimation();
			//if (attackState == 4)
			Audio::instance.voice.Play("pm/ataca");
		}
	}
	else if (dir.Magnitude() > 0) {
		if (state != "running") {
			state = "running";
			currentAnim = &runAnim;
			currentAnim->Reset();
		}
	}
	else state = "idle";

	//duringAnimation
	
	if (state == "stunning") {
		if (vibrationCounter > 0) {
			vibration = Vector2(-5 + rand() % 10, -5 + rand() % 10);
			vibrationCounter -= Kang::gameTimeSpeed;
		}
		if (stunedCounter > 0) {
			stunedCounter -= Kang::gameTimeSpeed;
		}
		if (stunedCounter <= 0) {
			vibration = Vector2();
			inmuneTimeCounter = inmuneTime;
		}
	}
	else if (state == "acuatic")
		currentAnim = &dashAnim;
	else if (state == "attacking") {
		if (currentAnim->HasEnded()) {
			bool hasTryYell = minimunShutTimeCounter <= 0;
			for (int i = 0; i < Collider::colliders.placerScope; i++) {
				auto c = Collider::colliders[i];
				if (*c->isActive) {
					if (c->layer == 1)
						if (ColliderManager::Colliding(c, &attackCollider)) {
							ObjetosInteracbles* ob = ((ObjetosInteracbles*)c->gameObject);
							ob->Throw(transform.position , fuerza.Get());
							Audio::instance.sfx.Play("effect/hit");
							
							if (ob->name == "silla")
								Audio::instance.sfx.Play("objetosInteracbles/silla");
							else if (ob->name == "maceta" || ob->name == "escritorio" || ob->name == "flecha" || ob->name == "anuncio")
								Audio::instance.sfx.Play("objetosInteracbles/maceta");
							else if (ob->name == "cajero01")
								Audio::instance.sfx.Play("recolectables/dinero");
							if (!hasTryYell) {
								hasTryYell = true;
								float r = rand() % 100;
								if (ob->name == "silla") {
									if (r < 25)
										if (mouthSoundTracker.TryToTrack("pm/kitatesilla", &Audio::instance.voice)) {
											DialogUI::instance.StartPopUp("pm");
										}
								}
								else if (r < 10) {
									if (mouthSoundTracker.TryToTrack("pm/noestorbencosas", &Audio::instance.voice)) {
										DialogUI::instance.StartPopUp("pm");
									}
								}
							}

							if (LevelState::instance.nEnemies > 0) {
								Vector2 dirAngle = (ob->transform.position - transform.position).Normalize();
								float nearest = 2000;
								Vector2* nearestV = nullptr;
								
								for (auto c : activeBeings) {
									if (c->gameObject->isActive) {
										if (*c->gameObject != *this) {
											Vector2 v = (transform.position - c->gameObject->transform.position);
											float dist = v.Magnitude();
											if (dist < nearest) {
												float difAngle = abs((dirAngle.GetAngle()) - (c->gameObject->transform.position - transform.position).GetAngle() );
												if (difAngle < Meth::PI * 1) {
													if (((dirAngle * v.Magnitude()) - v).Magnitude() < 1200) {
														nearestV = &c->gameObject->transform.position;
														nearest = dist;
													}
												}
											}
										}
									}
								}
								if (nearestV) {
									ob->AutoAim(*nearestV);
								}
							}
						}
					if (c->layer == 3)
						if (ColliderManager::Colliding(c, &attackCollider)) {
							Being* p = dynamic_cast<Being*>(c->gameObject);
							p->Damage(transform.position, damage.Get());
							Audio::instance.sfx.Play("effect/hit");
							if (!hasTryYell) {
								hasTryYell = true;
								std::string rs[] = { "pm/kitensetodos","pm/matese", "pm/pendejostodos", "pm/pagueme", "pm/demedinero" };
								float r = rand() % 100;
								if (r < 5) {
									int ir = rand() % 5;
									if (mouthSoundTracker.TryToTrack(rs[ir], &Audio::instance.voice)) {
										DialogUI::instance.StartPopUp("pm");
									}
								}
							}
						}
					if (c->layer == 4)
						if (ColliderManager::Colliding(c, &attackCollider)) {

							Bala* p = dynamic_cast<Bala*>(c->gameObject);
							p->speed = (p->transform.position - transform.position).Normalize() * p->speed.Magnitude() * 10;
							c->layer = -2;
						}
				}
			}
		}

		if (currentAnim->HasEnded())
			if (scheduledAttacks > 0) {
				AssingAttackAnimation();
				scheduledAttacks--;
			}else attacking = false;
	}
	else if (state == "running") {}
	else currentAnim = &idleAnim;
	currentAnim->Play(Kang::gameTimeSpeed);
}

void Player::AssingAttackAnimation() {
	if (attackState == 1)
		currentAnim = &attack1Anim;
	else if (attackState == 2)
		currentAnim = &attack2Anim;
	else if (attackState == 3)
		currentAnim = &attack3Anim;
	else if (attackState == 4)
		currentAnim = &attack4Anim;
	attackState++;
	if (attackState == 5)
		attackState = 1;
	currentAnim->Reset();
}




void Player::Draw() {
	
	if (currentAnim) {
		if ((int)inmuneTimeCounter % 7 != 0 || inmuneTimeCounter <= 0) {
			int dir = facingside ? 1 : -1;
			Vector2 spriteSize = Vector2(355, 200) * Cam::currentCam->zoom;
			RectTwoPoint spriteRectT = currentAnim->spriteRects[currentAnim->GetRealFrameBeingPlayed()];
			SDL_Rect r = ((Rect(spriteRectT.p1, spriteRectT.p2) + transform.position) + vibration).ToSDLRect();
			attackCollider.offset = Vector2(30 * dir, 0);
			SDL_Point p = { r.w / 2, r.h / 2 };
			FigureDrawer::DrawTexture(currentAnim->it,r, Color(255),!facingside);
			//SDL_RenderCopyEx(SDLClass::renderer, currentAnim->it, NULL, &r, Meth::RadToDeg(Cam::currentCam->rotation), &p, facingside ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	
		}
	}
}

void Player::Collisions() {
	FalseAllCollidingSides();
	bool r = !facingside;

	InvisibleWall::CollisionsWithAllBlocks(r, &bodyCollider, &movement, nullptr);

}

void Player::FalseAllCollidingSides() {
	for (int i = 0; i < 4; i++) {
		sidesColliding[i] = false;
	}
}

PlaceableObject* Player::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	currentAnim = &idleAnim;
	stunedCounter = 0;
	yellTime = 0;
	attackState = 1;
	vibrationCounter = 0;
	cam.StopVibration();
	cam.StopZoomAnimation();
	inmuneTimeCounter = 0;
	Being::Reset(this,100, 15, 2, 5);
	PlayerVariables::instance.money = 0;
	PlayerVariables::instance.liquid = 0;
	PlayerVariables::instance.acuatic = &dashing;
	return this;
}

PlaceableObject* Player::GetPlaceableObject(bool force) {
	if (!force) {
		if (isActive) {
			DeactivateAll();
			return nullptr;
		}
	}
	return this;
}

bool Player::AllUsed() {
	return isActive;
}

void Player::DeactivateAll() {
	isActive = false;
	exists = false;
}