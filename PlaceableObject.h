#pragma once
#include "GameObject.h"
#include "Scoper.hpp"
struct PlaceableObject : public GameObject
{	
	PlaceableObject();
	bool hasSettings;
	bool needSecondPos;
	float spawnSquashCounter;
	virtual void SetSettings();
	virtual PlaceableObject* Set(Vector2 pos, int ID);
	virtual PlaceableObject* GetPlaceableObject(bool force = false) = 0;
	virtual bool AllUsed() = 0;
	virtual void DeactivateAll() = 0;
	virtual void DeactivateAllType(int ID);
	virtual void EditorUpdate() {}
	virtual void EditorDraw();
	virtual void SetSecondPos(Vector2 pos);
};