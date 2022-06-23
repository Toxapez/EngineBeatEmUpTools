#pragma once
#include "Scoper.hpp"
#include "ColliderManager.h"
#include "Audio.h"
#include "Stat.h"


struct Being
{
	static Collider* playerHitCollider;
	static Scoper10000<Being*> beings;
	static std::list<Being*> activeBeings;
	Being();
	Stat maxHealth, speed, damage, fuerza;
	float health, stun;

	virtual void Damage(Vector2 pos ,float d);
	virtual void Dead();
	BoxCollider* collider;
	GameObject* gameObject;
	bool isOnScreen;

	void Reset(GameObject* g, float h, float s, float d = 0, float f = 0);
	void Heal(float h);
	
	static float minimunShutTime;
	static float minimunShutTimeCounter;
	float vibrationCounter;
	Vector2 vibration;
	static void SomeoneTalked() {
		minimunShutTimeCounter = minimunShutTime;
	}
};

