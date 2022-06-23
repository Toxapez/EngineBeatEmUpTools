#pragma once
#include "PlaceableObject.h"
#include "SpriteStatic.h"
#include "EmergentMessage.h"
#include "Console.h"
#include "Player.h"
class Door : public PlaceableObject
{
	static SpriteStatic editorSprite;
public:
	int doorNumber;
	std::string destinyLevelName;
	int destinyDoorNumber;
	static std::string loadLevel;
	static int loadLevelDoorN;
	static Scoper10<Door> placerScope;
	bool entrable;
	Door();
	void Update() override;
	void Draw() override;
	void EditorDraw() override;
	void AfterStaticStart();
	void SetSettings() override;

	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

