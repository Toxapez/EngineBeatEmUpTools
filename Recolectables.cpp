#include "Recolectables.h"

Scoper50<Animation> Recolectables::animations;
SpriteSheet Recolectables::lesheShaboSS;

Scoper100<Recolectables> Recolectables::scoper;
Color Recolectables::brilloColor = Color(255,255,0);

void Recolectables::Update() {
	if (playAnim) {
		currentAnim.Play(Kang::gameTimeSpeed);
		if (currentAnim.HasEnded())
			isActive = false;
	}
	else {
		
	}
	if (spawnSquashCounter > 0) {
		spawnSquashCounter -= Kang::gameTimeSpeed * .2;
	}

	touch = ColliderManager::Colliding(Being::playerHitCollider, &circleCollider);

	if (touch && !touched) {
		if (name == "dinero") {
			isActive = false;
			PlayerVariables::instance.money += 10;
			Audio::instance.sfx.Play("recolectables/dinero");

		}
		else if (name == "sangre") {
			if(*PlayerVariables::instance.acuatic)
				if (!playAnim) {
					PlayerVariables::instance.liquid += 10;
					playAnim = true;
				}
		}
		else if (name == "lesheShabo") {
			if (PlayerVariables::instance.handObject.name != "") {
				auto& o = PlayerVariables::instance.handObject;
				auto& po = scoper.GetNextScope();
				po.Set(o.name, Being::playerHitCollider->gameObject->transform.position + Vector2(0,60), o.nS);
			}
			isActive = false;
			PlayerVariables::instance.handObject.Set(name, nSlotSS,currentSS,nSlotSS,currentSS->infos[nSlotSS].first, currentSS->infos[nSlotSS].second);
		}
	}

	if (brilloCounter >= brilloTime)
		brilloCounter -= brilloTime;
	brilloCounter += Kang::gameTimeSpeed;

	touched = touch;

}


void Recolectables::Draw() {
	Color c = brilloCounter >= brilloTime - 5 ? brilloColor : overcolor;
	SDL_Rect r;
	Vector2 squash = Vector2(1, 1);
	if (spawnSquashCounter > 1.5)
		squash = Vector2(1.2, .3);
	else if (spawnSquashCounter > 0)
		squash = Vector2(.5, 1.5);


	if (nSlotSS == -1) {
		spriteRect = currentAnim.spriteRects[currentAnim.GetRealFrameBeingPlayed()];
		SDL_Point p = SDL_Point();
		//SDL_SetTextureColorMod(currentAnim.it, c.r, c.g, c.b);
		r = ((Rect(Vector2(spriteRect.p1.x * squash.x, spriteRect.p1.y * squash.y), Vector2(spriteRect.p2.x * squash.x, spriteRect.p2.y * squash.y)) + transform.position)).ToSDLRect();
		//SDL_RenderCopyEx(SDLClass::renderer, currentAnim.it, NULL, &r, 0, &p, SDL_FLIP_NONE);
		FigureDrawer::DrawTexture(currentAnim.it, r,c);
		//SDL_SetTextureColorMod(currentAnim.it, 255, 255, 255);
	}
	else {
		//SDL_SetTextureColorMod(currentSS->baseSprite.it, c.r, c.g, c.b);
		currentSS->Draw(nSlotSS, transform.position,true,true,0,SDL_Rect(),1,squash);
		//SDL_SetTextureColorMod(currentSS->baseSprite.it, 255, 255, 255);
	}
}

void Recolectables::AfterStaticStart() {
	if (animations[0].dir == "") {
		animations[0].Set("recolectables/dinero");
		animations[1].Set("recolectables/charco");
		lesheShaboSS.baseSprite.Set("recolectables/leshes.png");
		lesheShaboSS.Set(Vector2(50,50),7,7);
	}
}

Recolectables::Recolectables() {
	Vector2 spriteSize = Vector2(355, 200);
	spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	isActive = false;
	layer = 0;
	circleCollider.Set(Vector2(), 0, this);
	//circleCollider.drawable = true;
}

void Recolectables::Set(std::string n, Vector2 pos, int nS) {
	brilloCounter = 0;
	brilloTime = 70;
	nSlotSS = -1;
	spawnSquashCounter = 2;
	isActive = true;
	transform.position = pos;
	circleCollider.Set(Vector2(), 0, this);
	overcolor = Color();
	touched = true;
	playAnim = false;
	layer = 0;
	if (n == "dinero") {
		currentAnim = animations[0];
		currentAnim.Reset();
		circleCollider.Set(Vector2(0, 50), 25, this);
		name = n;
	}
	else if (n == "lesheShabo") {
		name = n;
		nSlotSS = nS;
		currentSS = &lesheShaboSS;
		circleCollider.Set(Vector2(0, 50), 25, this);
	}else if (n == "sangre") {
		currentAnim = animations[1];
		currentAnim.Reset();
		circleCollider.Set(Vector2(0, 0), 40, this);
		name = n;
		overcolor = Color(255,0,0);
		layer = -1;
	}

}