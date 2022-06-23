#pragma once
#include "PlaceableObject.h"
#include "SpriteStatic.h"
#include "ColliderManager.h"
#include "Particle.h"
#include "Being.h"
#include "Audio.h"
#include "Events.h"
#include "LevelState.h"
#include "Reader.h"
#include <pla.h>
#include  "ShadowCaster.h"

struct ObjetoInteracbleInitInfo {
	std::string name;
	Vector2 defaultCS;
	Vector2 offset;
	int durability;
};

class ObjetosInteracbles : public PlaceableObject
{
	static std::map<std::string,SpriteStatic> sprites;
	SpriteStatic* currentSprite;
	float durability;
	float impulso;
	void Update() override;
	void Draw() override;
	void EditorDraw() override {};
	void AfterStaticStart() override;
	void SetSettings() override {};
	float fuerza;
	std::vector<ShadowCaster* > casters;

	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override {
		if (!force) {
			if (AllUsed()) {
				DeactivateAll();
				return nullptr;
			}
		}
		return &placerScope.GetNextScope();
	}
	bool AllUsed() override {
		return placerScope.placerScope + 1 == placerScope.maxEntities;
	}
	void DeactivateAll() override {
		for (int i = 0; i < placerScope.maxEntities; i++) {
			placerScope[i].isActive = false;
			placerScope[i].exists = false;
		}
		placerScope.placerScope = 0;
	}

	void DeactivateAllType(int ID) override {
		ID -= 7;
		for (int i = 0; i < placerScope.maxEntities; i++) {
			if (placerScope[i].name == ois[ID].name) {
				placerScope[i].isActive = false;
				placerScope[i].exists = false;
			}
		}
		placerScope.placerScope = 0;
	}
	
	BoxCollider collider;
	Vector2 speed;
	float rotation;
	bool facing;
	float facingFlipCounter;
	float facingFlipSpeed;
public:
	static int offsetObjects;
	static void ReadAllObjects();
	static std::vector<ObjetoInteracbleInitInfo> ois;
	void AutoAim(Vector2 pos);
	std::string name;
	ObjetosInteracbles();
	static Scoper500<ObjetosInteracbles> placerScope;
	void SetType(int ID);
	void Throw(Vector2 otherPos, float f);
};

