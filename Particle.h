#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "RectTwoPoint.h"
#include "Rect.h"
#include "Cam.h"
#include "FigureDrawer.h"

class Particle : public GameObject
{
	static Scoper50<Animation> animations;
	int timing;
	void AfterStaticStart();
	Animation currentAnim;
	bool hasAnimation;
	RectTwoPoint spriteRect;
	void Update() override;
	void Draw() override;
	bool facing;
public:
	static Scoper100<Particle> scoper;
	Particle();
	void Set(std::string name, Vector2 pos, bool facing = true);
};
