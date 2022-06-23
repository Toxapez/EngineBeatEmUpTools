#pragma once
#include "PlaceableObject.h"
#include "EmergentMessage.h"
#include "Console.h"
#include "SpriteStatic.h"
#include <map>
#include <filesystem>
#include "Player.h"
#include "DialogUI.h"
#include "LevelState.h"
class NPC : public PlaceableObject 
{
	
	bool dissapear;
	void Update();
	void Draw();
	bool playernear;
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
	bool hasSpeak;
	SpriteStatic* exclamationSpr;
	SpriteStatic* indicationSpr;
	void AfterStaticStart();

public:
	static std::map<std::string, SpriteStatic> sprites;
	SpriteStatic* currentSprite;
	std::string name;
	std::string firstTimeDialog;
	std::string repeatDialog;
	std::string customConfig;
	NPC();
	void SetSettings();
	static Scoper50<NPC> placerScope;

};

