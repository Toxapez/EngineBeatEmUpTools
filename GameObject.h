#pragma once
#include "Scoper.hpp"
#include "Keyboard.h"
#include <list>
#include "Transform.h"
#include "Kang.h"


struct GameObject
{
	int uniqueID;
	static int idCounter;

	static Scoper100000<GameObject*> gameObjects;
	static std::list<GameObject*> upperLayerList;
	static std::list<GameObject*> dinamicLayerList;
	static std::list<GameObject*> downLayerList;
	bool isActive;
	bool placeableObject;
	bool resistant;
	bool exists;
	bool camDependent;
	int layer;
	
	Transform transform;
	GameObject();
	virtual void Update();
	virtual void Draw();
	virtual void AfterStaticStart();
	static void ArrangeLayers();
	static void AllAfterStaticStart();
	bool operator==(GameObject other);
	bool operator!=(GameObject other);
};

