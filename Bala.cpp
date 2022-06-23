#include "Bala.h"
Scoper50<Animation> Bala::animations;
Scoper100<Bala> Bala::scoper;

Bala::Bala() {
	Vector2 spriteSize = Vector2(355, 200);
	spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	isActive = false;
	circleCollider.Set(Vector2(),0,this);
	circleCollider.layer = 4;
	boxCollider.Set(Vector2(),Vector2(),this);
	//boxCollider.drawable = true;
}

void Bala::AfterStaticStart() {
	if (animations[0].dir == "") {
		animations[0].Set("balas/bolsa1");
		animations[1].Set("balas/papeles1");
	}
}

void Bala::Update() {
	currentAnim.Play(Kang::gameTimeSpeed);

	if (name == "bolsa1") {
		rotation += 13;
		if (circleCollider.layer == 4) {
			if (ColliderManager::Colliding(Being::playerHitCollider, &circleCollider)) {
				dynamic_cast<Being*>(Being::playerHitCollider->gameObject)->Damage(transform.position, damage);
			}
		}
		else {
			for (int i = 0; i < Collider::colliders.placerScope; i++) {
				auto c = Collider::colliders[i];
				if (*c->isActive) {
					if (c->layer == 3)
						if (ColliderManager::Colliding(c, &circleCollider)) {
							dynamic_cast<Being*>(c->gameObject)->Damage(transform.position, damage);
							isActive = false;
							exists = false;
							Particle::scoper.GetNextScope().Set("impacto1", transform.position);
							Audio::instance.sfx.Play("effect/hit");
						}
				}
			}
		}
	}
	else if (name == "papeles1") {
		if (ColliderManager::BoxBoxEdgesInside(&boxCollider, dynamic_cast<BoxCollider*>(Being::playerHitCollider) )) {
			dynamic_cast<Being*>(Being::playerHitCollider->gameObject)->Damage(transform.position, damage);
		}
	}

	if (deadTime > 0) {
		deadTime -= Kang::gameTimeSpeed;
		if (deadTime <= 0)
			isActive = false;
	}
	transform.position += speed * Kang::gameTimeSpeed;
	if (animationDeadEnd) if (currentAnim.HasEnded()) isActive = false;
}


void Bala::Draw() {
	SDL_Rect r = ((Rect(spriteRect.p1 * Cam::currentCam->zoom, spriteRect.p2 * Cam::currentCam->zoom) + transform.position)).ToSDLRect();
	Vector2 p = Vector2(r.w/2, r.h/2);
	FigureDrawer::DrawTexture(currentAnim.it, r,Color(255),false,false,Meth::DegToRad(rotation),p);
	//SDL_RenderCopyEx(SDLClass::renderer, currentAnim.it, NULL, &r, rotation, &p, SDL_FLIP_NONE);
}

void Bala::Set(std::string n, Vector2 pos, Vector2 s, float d) {
	isActive = true;
	transform.position = pos;
	deadTime = -1;
	animationDeadEnd = false;
	outOfScreenDead = false;
	exists = false;
	resistant = true;
	name = n;
	rotation = 0;
	damage = d;
	speed = s;
	circleCollider.Set(Vector2(), 0, this);
	boxCollider.Set(Vector2(), Vector2(), this);
	if (n == "bolsa1") {
		currentAnim = animations[0];
		currentAnim.Reset();
		outOfScreenDead = true;
		circleCollider.Set(Vector2(), 30, this);
	}else if (n == "papeles1") {
		currentAnim = animations[1];
		currentAnim.Reset();
		animationDeadEnd = true;
		Vector2 colliderSize = Vector2(160, 70);
		Vector2 colliderOffset = Vector2(0, 20);
		boxCollider.Set(colliderSize * -.5 + colliderOffset, colliderSize * .5 + colliderOffset, this);
	}
	if (outOfScreenDead) {
		exists = true;
		resistant = false;
	}
}





