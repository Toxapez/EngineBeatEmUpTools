#pragma once
#include "CamMovible.h"
#include "PlaceableObject.h"
#include "FigureDrawer.h"
#include "Player.h"
class CamBoundArea : public PlaceableObject
{
	void Update();
	void EditorDraw();
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
public:
	Vector2 secondPos;
	CamBoundArea();
	BoxCollider collider;
	CameraBounds camBounds;
	static Scoper50<CamBoundArea> placerScope;
	void SetSecondPos(Vector2 pos);
};
