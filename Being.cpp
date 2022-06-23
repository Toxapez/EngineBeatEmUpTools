#include "Being.h"

Scoper10000<Being*> Being::beings;
Collider* Being::playerHitCollider = nullptr;
float Being::minimunShutTime = Meth::SegToFrame(5);
float Being::minimunShutTimeCounter = 0;
std::list<Being*> Being::activeBeings;

Being::Being() {
	beings.GetNextScope() = this;
	
}

void Being::Damage(Vector2 pos, float d) {
	health -= d;
	if (health <= 0)
 		Dead();
}

void Being::Dead() {
	Audio::instance.sfx.Play("effect/muerte");
}

void Being::Heal(float h) {
	if (health + h < maxHealth.Get())
		health += h;
	else health = maxHealth.Get();
}

void Being::Reset(GameObject* g,float h, float s, float d, float f) {
	maxHealth.Reset();
	speed.Reset();
	damage.Reset();
	fuerza.Reset();

	maxHealth.Set(h);
	health = maxHealth.Get();
	speed.Set(s);
	damage.Set(d);
	fuerza.Set(f);

	gameObject = g;
	activeBeings.push_back(this);
}