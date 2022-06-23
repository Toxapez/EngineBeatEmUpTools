#pragma once
#include "GameObject.h"
#include "Scoper.hpp"
#include "FigureDrawer.h"
#include "ColliderManager.h"
#include "Animation.h"
#include "RectTwoPoint.h"
#include "Being.h"
#include "Particle.h"
struct Bala : public GameObject
{
	static Scoper50<Animation> animations;
	Animation currentAnim;
	Vector2 speed;
	CircleCollider circleCollider;
	RectTwoPoint spriteRect;
	BoxCollider boxCollider;
	float deadTime;
	bool animationDeadEnd;
	bool outOfScreenDead;
	std::string name;
	float rotation;
	float damage;
	void Update() override;
	void Draw() override;
	static Scoper100<Bala> scoper;
	Bala();
	void Set(std::string name,Vector2 pos, Vector2 speed, float d);
	void AfterStaticStart();
};

