#pragma once
#include "Animation.h"
#include "ColliderManager.h"
#include "Player.h"
#include "PlaceableObject.h"
#include "Being.h"
#include "Particle.h"
#include "Audio.h"
#include "GlobalStaticVariables.h"
#include "LevelState.h"
#include "DialogUI.h"
#include "DropPool.h"
class Enemy : public PlaceableObject, public Being
{
public:
	Enemy();
	Color damageColor;
	float damageColorCounter;
	static Player* objective;
	Animation currentAnim;
	Animation* idleAnim,* runAnim, * damagedAnim, * deadAnim, * attackAnim;
	RectTwoPoint spriteRect;
	BoxCollider bodyCollider;
	Vector2 colliderSize;
	bool facingside;
	bool sidesColliding[4];
	void FalseAllCollidingSides();
	void EditorDraw() override {};
	void SetSettings() override {};
	virtual void CalculateFacingSide();
	float spawnSquashCounterDecrease;
	Vector2 dir, movement, vDistance, attackPoint;
	float attackColliderOffset;
	float talkingRange;
	float squashGolpe;
	void Damage(Vector2 pos, float d) override;
	void Dead();
	float distance;
	void Collisions();
	void NonMovementHandling();
	virtual void Animator();
	virtual void Movement();
	std::vector<std::string> rs;
	void ChangeRandomTalking();
	virtual std::string RandomTalking();
	std::string name;
	std::string state;
	float triggerRadius, attackRadius, attackDelay, attackDelayCounter;
	void LightUpdate();
	void Update() override;
	void Draw() override;
	void AfterStaticStart();
	CircleCollider pushCollider;
	CircleCollider attackCollider;
	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
	Animation cargaAnim;
	static AudioTracker enemiesMouth;
	bool carga;
	static std::vector<Enemy*> currentEnemies;
};

