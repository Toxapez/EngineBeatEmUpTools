#pragma once
#include "PlaceableObject.h"
#include "Being.h"
#include "Level.h"
#include "Console.h"
#include "ShadowCaster.h"
class InvisibleWall : public PlaceableObject
{
	static void CollideWithSolidBlock(int i, BoxCollider* c, Vector2* speed, bool* sidesColliding);
public:
	static Scoper500<InvisibleWall> placerScope;
	std::vector<ShadowCaster*> casters;
	bool castShadow;
	BoxCollider collider;
	InvisibleWall();
	void Update() override;
	void Draw() override;
	void EditorDraw() override;
	void AfterStaticStart();
	void SetSettings() override;


	static void CollisionsWithAllBlocks(bool b, BoxCollider* c, Vector2* speed, bool* sidesColliding);

	PlaceableObject* Set(Vector2 pos, int ID) override;
	PlaceableObject* GetPlaceableObject(bool force = false) override;
	bool AllUsed() override;
	void DeactivateAll() override;
};

