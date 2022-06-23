#include "Spawner.h"

Scoper5<Spawner> Spawner::placerScope;

Spawner::Spawner() {
	bodyCollider.layer = 0;
	Vector2 offset = Vector2(-20, 10);
	Vector2 colliderSize = Vector2(120, 70);
	bodyCollider.Set(colliderSize * -.5 + offset, colliderSize + offset, this);
	offset = Vector2(-20, -25);
	colliderSize = Vector2(120, 110);
	collider.Set(colliderSize * -.5 + offset, colliderSize + offset, this);
	collider.layer = 3;
	layer = 0;
	damageColor = Color(255, 170, 0);
}

void Spawner::Update() {
	spawnTimeCounter -= Kang::gameTimeSpeed;

	if (doorOpen > 0) {
		currentSpr = &sprDoorOpen;
		doorOpen -= Kang::gameTimeSpeed;
	}else currentSpr = &sprDoorClose;

	if (spawnTimeCounter <= 0) {
		spawnTimeCounter = spawnTime;
		float r = rand() % 100;
		Enemy* e;
		
		if (r < 10) 
			e = &Funcionaria::placerScope.GetNextScope();
		else if (r < 30) 
			e = &Guard::placerScope.GetNextScope();
		else 
			e = &Oficinista::placerScope.GetNextScope();
		

		if (e->isActive) 
			LevelState::instance.nEnemies--;
		e->Set(transform.position + Vector2(0, 150), 0);
		doorOpen = 15;
	}
	
	if (ladeacion > 0)
		ladeacion -= Kang::gameTimeSpeed;
	if (spawnSquashCounter > 0) {
		spawnSquashCounter -= Kang::gameTimeSpeed * .2;
	}
	if (damageColorCounter > 0)
		damageColorCounter -= Kang::gameTimeSpeed;

	if (Keyboard::KeyboardCheck(SDL_SCANCODE_LALT)) {
		if (Keyboard::KeyboardPressed(SDL_SCANCODE_1)) {
			Damage(transform.position, 100000);
		}
	}
}

void Spawner::Damage(Vector2 pos, float d) {
	Being::Damage(pos,d);
	ladeacion = 10;
	damageColorCounter = 10;
	Audio::instance.sfx.Play("effect/metalgolpeado");
}
void Spawner::Dead() {
	isActive = false;
	exists = false;
	Audio::instance.sfx.Play("effect/metal");
	LevelState::instance.nEnemies--;
}

void Spawner::Draw() {
	Vector2 spriteSize = Vector2(355, 200) * Cam::currentCam->zoom;
	RectTwoPoint spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	SDL_Rect r;
	Color c = damageColorCounter > 0 ? damageColor : Color();
	//SDL_SetTextureColorMod(currentSpr->it, c.r, c.g, c.b);
	Vector2 squash = Vector2(1,1);
	if (spawnSquashCounter > 1.5) 
		squash = Vector2(1.2,.3);
	else if (spawnSquashCounter > 0) 
		squash = Vector2(.5, 1.5);
	r = ((Rect(Vector2(spriteRect.p1.x * squash.x, spriteRect.p1.y * squash.y), Vector2(spriteRect.p2.x * squash.x, spriteRect.p2.y * squash.y)) + transform.position)).ToSDLRect();
	currentSpr->Draw(transform.position,true,ladeacion > 0 ? .1:0, r);
	Vector2 lifeBarPos = Vector2(0, -120) * Cam::currentCam->zoom;
	Vector2 lfSize = Vector2(155, 16);
	FigureDrawer::DrawFillRectRef(Rect(lifeBarPos, lfSize),Color(204,101,2),transform);
	FigureDrawer::DrawFillRectRef(Rect(lifeBarPos - (lfSize/2 * Cam::currentCam->zoom), Vector2(lfSize.x * (health /17), lfSize.y) * Cam::currentCam->zoom), Color(255, 204, 2), transform,false);
	FigureDrawer::DrawRectRef(Rect(lifeBarPos, lfSize), Color(0), transform);
}

PlaceableObject* Spawner::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	type = ID;
	currentSpr = &sprDoorClose;
	ladeacion = 0;
	spawnTime = Meth::SegToFrame(3);
	spawnTimeCounter = spawnTime;
	health = 17;
	LevelState::instance.nEnemies++;
	damageColorCounter = 0;
	vibrationCounter = 0;
	return this;
}

void Spawner::AfterStaticStart() {
	sprDoorOpen.Set("spawner/1/abierto.png", Vector2(355, 200));
	sprDoorClose.Set("spawner/1/cerrado.png", Vector2(355, 200));
}