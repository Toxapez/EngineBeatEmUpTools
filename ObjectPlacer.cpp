#include "ObjectPlacer.h"

void ObjectPlacer::FillList() {
	currentBrushNumber = 0;

	AddNewLayer();
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Player", &Player::player));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Oficinistas", &Oficinista::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Guard", &Guard::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Tank", &Tank::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Empleado", &Empleado::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Funcionaria", &Funcionaria::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Dinerin", &Dinerin::placerScope[0]));
	ObjetosInteracbles::offsetObjects = globalPlaceableObjects[0].size();
	ObjetosInteracbles::ReadAllObjects();
	for (auto c : ObjetosInteracbles::ois)
		globalPlaceableObjects[0].push_back(PlaceableObjectInfo(c.name, &ObjetosInteracbles::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("Spawner", &Spawner::placerScope[0]));
	globalPlaceableObjects[0].push_back(PlaceableObjectInfo("NPC", &NPC::placerScope[0]));

	AddNewLayer();
	BGItems::ReadAllSprites();
	for (auto c : BGItems::names)
		globalPlaceableObjects[1].push_back(PlaceableObjectInfo(c, &BGItems::placerScope[0]));

	AddNewLayer();
	globalPlaceableObjects[2].push_back(PlaceableObjectInfo("walls", &InvisibleWall::placerScope[0]));
	globalPlaceableObjects[2].push_back(PlaceableObjectInfo("Door", &Door::placerScope[0]));

	AddNewLayer();
	Tapiz::ReadAllColors();
	for (auto c : Tapiz::names)
		globalPlaceableObjects[3].push_back(PlaceableObjectInfo(c, &Tapiz::placerScope[0]));

	AddNewLayer();
	globalPlaceableObjects[4].push_back(PlaceableObjectInfo("CamBound", &CamBoundArea::placerScope[0]));

	AddNewLayer();
	globalPlaceableObjects[5].push_back(PlaceableObjectInfo("PostIt", &Postit::placerScope[0]));


	levelTemp.nWaves = &currentLevel->nWaves;
	currentWaveNumber = 0;
}

void ObjectPlacer::AddNewBGItem() {
	globalPlaceableObjects[1].push_back(PlaceableObjectInfo(BGItems::names.back(), &BGItems::placerScope[0]));
}

PlaceableObject* ObjectPlacer::Place(int ID, Vector2 pos) {
	while (true) {
		PlaceableObject* r;
		r = GetCurrentSelectedPO(ID);
		if (PlaceableObject* r = globalPlaceableObjects[currentBrushNumber][usedPlaceableObjects[currentBrushNumber][ID]].list->GetPlaceableObject()) {
			
			return r->Set(pos, usedPlaceableObjects[currentBrushNumber][ID]);
		}
		ReplaceAllofAnObject(ID);

		if (r->AllUsed()) {
			return nullptr;
		}
	}
}

PlaceableObject* ObjectPlacer::GetCurrentSelectedPO(int ID) {
	return globalPlaceableObjects[currentBrushNumber][usedPlaceableObjects[currentBrushNumber][ID]].list;
}

void ObjectPlacer::ReplaceAllofAnObject(int ID) {
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			if (currentLevel->levelLayers->content[i][j] == ID) {
				levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].second = Place(ID, GetTilePosFromTileCoor(Vector2(i, j)));
				
			}
		}
	}

}

Vector2 ObjectPlacer::GetTilePosFromTileCoor(Vector2 p) {
	return Vector2(p.x * LEVELTILESIZE, p.y  * LEVELTILESIZE);
}

void ObjectPlacer::EmptyLevel() {
	for (auto c : globalPlaceableObjects) {
		for (int i = 0; i < c.size(); i++) {
			c[i].list->DeactivateAll();
		}
	}
}

void ObjectPlacer::LoadLevel(Level* l, bool exists) {
	for (int k = 0; k < nLevelLayers; k++) {	
		currentBrushNumber = k;
		bool unputtedInfo[LEVELSIZEX][LEVELSIZEY];
		for (int i = 0; i < LEVELSIZEY; i++)
			for (int j = 0; j < LEVELSIZEX; j++)
				unputtedInfo[i][j] = true;
		for (int i = 0; i < LEVELSIZEY; i++) {
			for (int j = 0; j < LEVELSIZEX; j++) {
				if (unputtedInfo[i][j]) {
					unputtedInfo[i][j] = false;
					int ID = l->levelLayers[k].content[i][j];
					if (ID != EMPTYTILEVALUE) {
						PlaceableObject* p = Place(ID, GetTilePosFromTileCoor(Vector2(i, j)));
						levelTemp.levelLayers[k].baselayer[i][j].second = p;
						levelTemp.levelLayers[k].baselayer[i][j].second->exists = exists;
						if (exists) {
							if (currentBrushNumber == 2) {
								if (ID == 0) {
									std::vector<Vector2> walls;
									int cc = 1;
									InvisibleWall* iw = dynamic_cast<InvisibleWall*>(p);
									while (l->levelLayers[k].content[i][j + cc] == 0 && unputtedInfo[i][j + cc])
										cc++;
									if (cc == 1) {
										while (l->levelLayers[k].content[i + cc][j] == 0 && unputtedInfo[i + cc][j ])
											cc++;
										if (cc > 1) {
											iw->collider.Set(Vector2(), Vector2(LEVELTILESIZE * cc, LEVELTILESIZE), iw);
											iw->castShadow = true;
											for (int kk = 1; kk < cc; kk++)
												unputtedInfo[i + kk][j] = false;
										}
									}
									else {
										iw->collider.Set(Vector2(), Vector2(LEVELTILESIZE, LEVELTILESIZE * cc), iw);
										iw->castShadow = true;
										for (int kk = 1; kk < cc; kk++)
											unputtedInfo[i][j + kk] = false;
									}
									
								}
							}
							else if (currentBrushNumber == 3) {
								if (ID == 1) {
									Tapiz* tapiz = dynamic_cast<Tapiz*>(p);
									tapiz->border[0] = l->levelLayers[k].content[i][j - 1] != ID;
									tapiz->border[1] = l->levelLayers[k].content[i - 1][j] != ID;
									tapiz->border[2] = l->levelLayers[k].content[i + 1][j] != ID;
									tapiz->border[3] = l->levelLayers[k].content[i][j + 1] != ID;
																	  
									tapiz->corner[0] = l->levelLayers[k].content[i - 1][j - 1] != ID;
									tapiz->corner[1] = l->levelLayers[k].content[i + 1][j - 1] != ID;
									tapiz->corner[2] = l->levelLayers[k].content[i - 1][j + 1] != ID;
									tapiz->corner[3] = l->levelLayers[k].content[i + 1][j + 1] != ID;
								}
							}
						}

					}
				}
			}
		}
	}
	currentBrushNumber = 0;

}

void ObjectPlacer::LoadWaveinEditor(Level* l, int nwave) {

	currentBrushNumber = 0;
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			int ID = l->waves[nwave].content[i][j];
			if (ID != EMPTYTILEVALUE) {
				levelTemp.waves[nwave].baselayer[i][j].second = Place(ID, GetTilePosFromTileCoor(Vector2(i, j)));
				levelTemp.waves[nwave].baselayer[i][j].second->exists = false;
			}
		}
	}
	//for (int k = 1; k < nLevelLayers; k++) {
	//	currentBrushNumber = k;
	//	for (int i = 0; i < LEVELSIZEY; i++) {
	//		for (int j = 0; j < LEVELSIZEX; j++) {
	//			int ID = l->levelLayers[k].content[i][j];
	//			if (ID != EMPTYTILEVALUE) {
	//				levelTemp.levelLayers[k].baselayer[i][j].second = Place(ID, GetTilePosFromTileCoor(Vector2(i, j)));
	//				levelTemp.levelLayers[k].baselayer[i][j].second->exists = false;
	//			}
	//		}
	//	}
	//}
	currentBrushNumber = 0;
}

std::vector<PlaceableObject*> ObjectPlacer::GetAllOfAnObject(int ID, int l, int w) {
	int olayer = currentBrushNumber;
	if (l != -1) {
		currentBrushNumber = l;
	}
	std::vector<PlaceableObject*> r;
	if (w < 0) {
		for (int i = 0; i < LEVELSIZEY; i++) {
			for (int j = 0; j < LEVELSIZEX; j++) {
				if (*levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].first == ID) {
					r.push_back(levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].second);
				}
			}
		}
	}else{
		if (currentBrushNumber == 0) {
			for (int i = 0; i < LEVELSIZEY; i++) {
				for (int j = 0; j < LEVELSIZEX; j++) {
					if (*levelTemp.waves[w].baselayer[i][j].first == ID) {
						r.push_back(levelTemp.waves[w].baselayer[i][j].second);
					}
				}
			}
		}
	}

	currentBrushNumber = olayer;
	return r;
}

void ObjectPlacer::EraseAllOfAnObject(int ID) {
	std::vector<PlaceableObject*> r;
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			if (*levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].first == ID) {
				*levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].first = EMPTYTILEVALUE;
			}
		}
	}
}

void ObjectPlacer::PushAllOfAnObject(int ID) {
	std::vector<PlaceableObject*> r;
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			if (*levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].first == ID) {
				*levelTemp.levelLayers[currentBrushNumber].baselayer[i][j].first = ID-1;
			}
		}
	}
}

int ObjectPlacer::GetCorrectLayer(int i) {
	int xd[] = {0,1,2,3,4,5};
	return xd[i];
}

void  ObjectPlacer::EraseFromGlosary(int ID) {
	EraseAllOfAnObject(ID);

	for (int i = ID; i < usedPlaceableObjects[currentBrushNumber].size(); i++)
		PushAllOfAnObject(i);
}

void ObjectPlacer::AddNewLayer() {
	usedPlaceableObjects.push_back(std::vector<int>());
	globalPlaceableObjects.push_back(std::vector<PlaceableObjectInfo>());
}