#include "Particle.h"
Scoper50<Animation> Particle::animations;
Scoper100<Particle> Particle::scoper;

void Particle::Update() {
	if (hasAnimation) {
		currentAnim.Play(Kang::gameTimeSpeed);
		if (currentAnim.HasEnded())
			isActive = false;
	}
}


void Particle::Draw() {
	if (hasAnimation) {
		SDL_Rect r = ((Rect(spriteRect.p1 * Cam::currentCam->zoom, spriteRect.p2 * Cam::currentCam->zoom) + transform.position)).ToSDLRect();
		SDL_Point p = SDL_Point();
		FigureDrawer::DrawTexture(currentAnim.it, r);
		//SDL_RenderCopyEx(SDLClass::renderer, currentAnim.it, NULL, &r, 0, &p, facing ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}

void Particle::AfterStaticStart() {
	if (animations[0].dir == "") {
		animations[0].Set("particulas/impacto1");
		animations[1].Set("particulas/sangre1");
		animations[2].Set("particulas/acuatico1");
	}
}

Particle::Particle() {
	Vector2 spriteSize = Vector2(355, 200);
	spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	isActive = false;
	layer = 0;
	
}

void Particle::Set(std::string name, Vector2 pos, bool f) {
	facing = f;
	hasAnimation = false;
	isActive = true;
	transform.position = pos;
	if (name == "impacto1") {
		currentAnim = animations[0];
		hasAnimation = true;
		currentAnim.Reset();
	}else if (name == "sangre1") {
		currentAnim = animations[1];
		hasAnimation = true;
		currentAnim.Reset();
	}
	else if (name == "acuatico1") {
		currentAnim = animations[2];
		hasAnimation = true;
		currentAnim.Reset();
	}
}