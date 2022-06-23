#pragma once
#include "PlaceableObject.h"
#include "SpriteStatic.h"
#include "Console.h"
#include "Level.h"
#include "Reader.h"
#include "FileUtilities.h"
class BGItems : public PlaceableObject
{
	static std::vector<SpriteStatic*> sprites;



public:
	static std::vector<std::string> names;
	static Scoper1000<BGItems> placerScope;
	SpriteStatic* currentSprite;
	BGItems();
	void Update() override;
	void Draw() override;
	void EditorDraw() override;
	void AfterStaticStart() override;
	void SetSettings() override {};

	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
	void DeactivateAllType(int ID) override {
		for (int i = 0; i < placerScope.maxEntities; i++) {
			if (sprites[ID] == placerScope[i].currentSprite) {
				placerScope[i].isActive = false;
				placerScope[i].exists = false;
			}
		}
		placerScope.placerScope = 0;
	}
	void SetSprite(int ID);
	static void ReadAllSprites();
	static bool CreateNew(std::string n, std::string dir, Vector2 os);
};

