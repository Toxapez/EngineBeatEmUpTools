#include "LevelEditor.h"

LevelEditor LevelEditor::instance;
bool LevelEditor::editting = true;

LevelEditor::LevelEditor() {
	camBounds = CameraBounds(RectTwoPoint(Vector2(), Vector2(LEVELSIZEX, LEVELSIZEY) * LEVELTILESIZE));
	cam.SetCamMovible((Vector2(LEVELSIZEX, LEVELSIZEY)/2) *LEVELTILESIZE,1,&camBounds);
	cam.speed = 12;
	cam.move = true;
	puttingObjectSelection = 0;
	
	objectPlacer.currentLevel = &currentLevel;
	objectGroups.push_back("Objects");
	objectGroups.push_back("Background");
	objectGroups.push_back("Structure");
	objectGroups.push_back("Paint");
	objectGroups.push_back("CamBounds");
	objectGroups.push_back("EditorUtilities");
	ogSelected = objectGroups.begin();
	ClearLevelTemp();
	layer = 5;
	itemOptionsWindowShowing = false;
}

void LevelEditor::LoadLevelFromFile(std::string n) {
	for (int i = 0; i < 4; i++)
		n.pop_back();
	currentLevel.SetName(n.c_str());
	config.clear();
	objectPlacer.currentLevel->Load(n, &config, wavesConfig, &objectPlacer.usedPlaceableObjects);
	LoadLevel(&currentLevel, !editting);
	UpdateConfig();
	hasMadeChanges = false;
	SDLClass::ChangeWindowTitle(currentLevel.name);
	
}

void LevelEditor::LoadLevel(Level* l, bool exists) {
	Being::activeBeings.clear();
	if (!editting) {
		LevelState::instance.nEnemies = 0;
		LevelState::instance.currentWave = 0;
		LevelState::instance.wavesActive = false;
	}
	if (objectPlacer.currentWaveNumber > 0 && editting) {
		objectPlacer.currentBrushNumber = 0;
		ogSelected = objectGroups.begin();
		objectPlacer.EmptyLevel();
		objectPlacer.LoadWaveinEditor(&currentLevel, objectPlacer.currentWaveNumber - 1);
		UpdateConfig();
	}
	else {
		objectPlacer.EmptyLevel();
		objectPlacer.LoadLevel(l, exists);
		UpdateConfig();
	}
}

void LevelEditor::WriteConfig() {
	config.clear();
	auto l = objectPlacer.GetAllOfAnObject(1, 2);
	for (auto c : l) {
		auto d = (Door*)c;
		config.push_back(std::to_string(d->doorNumber));
		config.push_back(d->destinyLevelName);
		config.push_back(std::to_string(d->destinyDoorNumber));
	}
	
	l = objectPlacer.GetAllOfAnObject(0, 4);
	for (auto c : l) {
		auto d = (CamBoundArea*)c;
		config.push_back(std::to_string(d->secondPos.x));
		config.push_back(std::to_string(d->secondPos.y));
	}
	l = objectPlacer.GetAllOfAnObject(0, 5);
	for (auto c : l) {
		auto d = (Postit*)c;
		config.push_back(d->message);
	}
	l = objectPlacer.GetAllOfAnObject(14, 0, objectPlacer.currentWaveNumber - 1);
	wavesConfig[objectPlacer.currentWaveNumber].clear();
	for (auto c : l) {
		auto d = (NPC*)c;
		wavesConfig[objectPlacer.currentWaveNumber].push_back(d->name);
		wavesConfig[objectPlacer.currentWaveNumber].push_back(d->firstTimeDialog);
		wavesConfig[objectPlacer.currentWaveNumber].push_back(d->repeatDialog);
		wavesConfig[objectPlacer.currentWaveNumber].push_back(d->customConfig);

	}

}

void LevelEditor::UpdateConfig() {
	auto it = config.begin();
	if (!config.empty())
	{
		if (config.size() >0)
		{
			std::vector<PlaceableObject*> l;
			l = objectPlacer.GetAllOfAnObject(1, 2);
			for (auto c : l) {
				auto d = (Door*)c;
				d->doorNumber = stoi(*it);				it++;
				d->destinyLevelName = *it;				it++;
				d->destinyDoorNumber = stoi(*it);		it++;

			}
			l = objectPlacer.GetAllOfAnObject(0, 4);
			for (auto c : l) {
				Vector2 sp;
				sp.x = stoi(*it);				it++;
				sp.y = stoi(*it);				it++;
				c->SetSecondPos(sp);
			}
			l = objectPlacer.GetAllOfAnObject(0, 5);
			for (auto c : l) {
				auto d = (Postit*)c;
				d->message = *it;	d->textbox.displayText.text = d->message;	it++;

			}
			
			l = objectPlacer.GetAllOfAnObject(14, 0, !editting ? LevelState::instance.currentWave-1 : objectPlacer.currentWaveNumber-1);
			it = wavesConfig[!editting ? LevelState::instance.currentWave : objectPlacer.currentWaveNumber].begin();
			for (auto c : l) {
				auto d = (NPC*)c;
				d->name = *it;				it++;
				d->firstTimeDialog = *it;	it++;
 				d->repeatDialog = *it;		it++;
				d->customConfig = *it;		it++;
				d->currentSprite = &d->sprites.at(d->name);
				
			}
		}
	}
}

void LevelEditor::Save() {
	
	objectPlacer.currentLevel->Save(&config, wavesConfig, objectPlacer.usedPlaceableObjects);
	hasMadeChanges = false;
	SDLClass::ChangeWindowTitle(currentLevel.name);
}

void LevelEditor::NewLevel(std::string n) {
	currentLevel.SetName(n.c_str());
	objectPlacer.EmptyLevel();
	MadeChange();
}

void LevelEditor::AfterStaticStart() {
	objectPlacer.FillList();
	SetActive(false);
}

void LevelEditor::SetActive(bool b) {
	isActive = b;
	cam.isActive = b;
	objectPlacer.EmptyLevel();
	if (b) {
		Cam::currentCam = &cam;
		objectPlacer.LoadLevel(&currentLevel, !editting);
		SDLClass::ChangeWindowTitle(currentLevel.name);
	}
}

void LevelEditor::MadeChange() {
	if (!hasMadeChanges) {
		SDLClass::ChangeWindowTitle("*" + std::string(currentLevel.name));
	}
	hasMadeChanges = true;
}







void LevelEditor::Update() {
	if (PlayerVariables::instance.user) {
		if (editting) {
			Cam::currentCam = &cam;
			cam.isActive = true;
			ogSelected = objectGroups.begin();
			puttingObjectSelection = 0;
			objectPlacer.currentBrushNumber = 0;
			DialogUI::instance.inDialog = false;
			cam.isActive = editting;
			LoadLevel(&currentLevel, !editting);

			editting = false;
			Cam::currentCam = &Player::player.cam;
			cam.isActive = editting;
			LoadLevel(&currentLevel, !editting);
		}
	}else if (Keyboard::KeyboardPressed(SDL_SCANCODE_F1)) {
		editting = !editting;
		if (editting) {
			Cam::currentCam = &cam;
			cam.isActive = true;
			ogSelected = objectGroups.begin();
			puttingObjectSelection = 0;
			objectPlacer.currentBrushNumber = 0;
			DialogUI::instance.inDialog = false;
		}
		else {
			Cam::currentCam = &Player::player.cam;
			cam.isActive = false;
		}
		cam.isActive = editting;
		LoadLevel(&currentLevel, !editting);
	}
	if (editting) {
		if (Keyboard::KeyboardCheck(SDL_SCANCODE_TAB)) {
			MoveWaveCurrentSelection();
		}
		else if (Keyboard::KeyboardCheck(SDL_SCANCODE_O)) {
			MoveWaveMaxNumberSelection();
		}else MovePuttingObjectSelection();

		if(objectPlacer.currentBrushNumber == 4)
			if (firstClick != Vector2()) {
				if (!Mouse::leftClickCheck) {
					secondClick = GetTileCoorFromWorldPos(Mouse::GetVector2PosRef(&cam));
					PutObject(firstClick);
					firstClick = Vector2();
					secondClick = Vector2();
				}
			}
		if (itemOptionsWindowShowing == 2) {
			int n = itemOptions.CollidingWithPoint(Mouse::GetVector2PosRef(Cam::currentCam));
			if (n > -1) {

				if (Mouse::leftClickPressed) { 
					auto a = std::find(objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].begin(), objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].end(), itemOptionsIndex[n]);
					objectPlacer.globalPlaceableObjects[objectPlacer.currentBrushNumber][itemOptionsIndex[n]].list->DeactivateAllType(itemOptionsIndex[n]);
					objectPlacer.EraseFromGlosary(n);
					objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].erase(a);
					itemOptionsWindowShowing = 0;

					if (puttingObjectSelection >= objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size())
						puttingObjectSelection = objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size() - 1;
				}

			}
		}
		else if (itemOptionsWindowShowing == 1) {
			int n = itemOptions.CollidingWithPoint(Mouse::GetVector2PosRef(Cam::currentCam));
			if (n > -1) {

				if (Mouse::leftClickPressed) {
					objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].push_back(itemOptionsIndex[n]);
					itemOptionsWindowShowing = 0;
					if (puttingObjectSelection < 0)
						puttingObjectSelection = 0;
				}
				
			}
		}
		else {
			//putting and erasing obj
			if (Mouse::leftClickCheck && Keyboard::KeyboardCheck(SDL_SCANCODE_LSHIFT)) {
				PutObject();
				firstClick = Vector2();
				secondClick = Vector2();
			}
			if (Mouse::leftClickPressed) {
				if (objectPlacer.currentBrushNumber == 4) firstClick = GetTileCoorFromWorldPos(Mouse::GetVector2PosRef(&cam));
				else PutObject();
			}
			else if (Mouse::rightClickPressed || (Mouse::rightClickCheck && Keyboard::KeyboardCheck(SDL_SCANCODE_LSHIFT))) {
				EraseObject();
			}
			if (Keyboard::KeyboardCheck(SDL_SCANCODE_I)) {

				if (Keyboard::KeyboardCheck(SDL_SCANCODE_LALT)) {
					DeleteObject(Mouse::GetVector2PosRef(Cam::currentCam));
				}
				else {
					AddObject(Mouse::GetVector2PosRef(Cam::currentCam));
				}
			}
		}
		if (Keyboard::KeyboardCheck(SDL_SCANCODE_LCTRL) && Keyboard::KeyboardPressed(SDL_SCANCODE_S)) {
			Save();
		}
		if (Keyboard::KeyboardFirstPressed(SDL_SCANCODE_ESCAPE)) {
			if(hasMadeChanges)
				if (BooleanQuestion::AskQuestion("Desea guardar antes de salir?")) 
					Save();
			objectPlacer.currentWaveNumber = 0;
			ChangeGameState(gamestates[0]);
		}
		if (Keyboard::KeyboardFirstPressed(SDL_SCANCODE_F2)) {
			EmergentMessage::ForceEmergentMessage("Introduzca nuevo nombre del nivel en la consola");
			std::cout << "Cambiando nombre del nivel, cambiar el nombre guardara los cambios.\nPara cancelar deje en blanco.\nIntroduzcan nuevo nombre:";
			std::string name;
			std::cin >> name;
			if (!name.empty()) {
				currentLevel.Delete();
				currentLevel.SetName(name.c_str());
				Save();
			}
		}
		
	}


	if (Door::loadLevel != "") {
		if (Door::loadLevel != currentLevel.name) {
			objectPlacer.EmptyLevel();
			LoadLevelFromFile(Door::loadLevel + ".lvl");
		}
		Door::loadLevel = "";
		auto l = objectPlacer.GetAllOfAnObject(1,2);
		for (auto c : l) {
			auto d = (Door*)c;
			if (d->doorNumber = Door::loadLevelDoorN) {
				d->entrable = false;
				Player::player.transform.position = d->transform.position;
				Console::SendLineMessage("Se encontro puerta de destino");
			}
		}
	}

	

}

void LevelEditor::AddObject(Vector2 menuSpawnPos) {
	if (objectPlacer.globalPlaceableObjects[objectPlacer.currentBrushNumber].size() > objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size()) {
		std::vector<std::string> names;
		int i = 0;
		itemOptionsIndex.clear();
		for (auto c : objectPlacer.globalPlaceableObjects[objectPlacer.currentBrushNumber]) {
			if (!std::count(objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].begin(), objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].end(), i)) {
				names.push_back(c.name);
				itemOptionsIndex.push_back(i);
			}
			i++;
		}
		itemOptions = OptionsBox(&transform.position, *ogSelected, Vector2(100, 30), names, menuSpawnPos);
		itemOptionsWindowShowing = 1;
	}
}
void LevelEditor::DeleteObject(Vector2 menuSpawnPos) {
	if (objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size() > 0) {
		std::vector<std::string> names;
		int i = 0;
		itemOptionsIndex.clear();
		for (auto c : objectPlacer.globalPlaceableObjects[objectPlacer.currentBrushNumber]) {
			if (std::count(objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].begin(), objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].end(), i)) {
				names.push_back(c.name);
				itemOptionsIndex.push_back(i);
			}
			i++;
		}
		itemOptions = OptionsBox(&transform.position, *ogSelected, Vector2(100, 30), names, menuSpawnPos);
		itemOptionsWindowShowing = 2;
	}
}

void LevelEditor::MoveWaveMaxNumberSelection() {
	if (Mouse::scrollUp) {
		if (*objectPlacer.levelTemp.nWaves != 0 && objectPlacer.currentWaveNumber < *objectPlacer.levelTemp.nWaves) {
			(*objectPlacer.levelTemp.nWaves)--;
			MadeChange();
		}
	}
	else if (Mouse::scrollDown) {
		if (*objectPlacer.levelTemp.nWaves != nLevelWaves) {
			(*objectPlacer.levelTemp.nWaves)++;
			MadeChange();
		}
	}
}

void LevelEditor::MoveWaveCurrentSelection() {
	bool moved = false;
	if (Mouse::scrollUp) {
		if (*objectPlacer.levelTemp.nWaves > 0) {
			objectPlacer.currentWaveNumber--;
			moved = true;

			if (objectPlacer.currentWaveNumber == -1) {
				objectPlacer.currentWaveNumber = *objectPlacer.levelTemp.nWaves;
			}
		}
	}
	else if (Mouse::scrollDown) {
		if (*objectPlacer.levelTemp.nWaves >= objectPlacer.currentWaveNumber) {
			objectPlacer.currentWaveNumber++;
			moved = true;

			if (objectPlacer.currentWaveNumber > *objectPlacer.levelTemp.nWaves) {
				objectPlacer.currentWaveNumber = 0;
			}
		}
	}
	if (moved) {
		
		LoadLevel(&currentLevel, exists);
	}

}

void LevelEditor::Draw() {
	if (editting) {
		DrawGrind();
		if (itemOptionsWindowShowing > 0)
			itemOptions.Draw();
		else
			DrawPuttingObjectSelectedName();
		FigureDrawer::DrawFillRect(Rect(200,70),Color(0,0,200));
		std::string wavename = objectPlacer.currentWaveNumber == 0 ? "Base" : std::to_string(objectPlacer.currentWaveNumber);
		TextDrawer::DrawSimpleText(Text("Wave: " +wavename, 15,Color(255),"arial"), Vector2(10, 10));
		TextDrawer::DrawSimpleText(Text("MaxWaves: " + std::to_string(*objectPlacer.levelTemp.nWaves), 15, Color(255), "arial"), Vector2(10, 25));

		
	}
}

void LevelEditor::DrawGrind() {
	Color c = Color(55);
	int maxY = LEVELSIZEY * LEVELTILESIZE * Cam::currentCam->zoom;
	for (int i = 1; i < LEVELSIZEX ;i++) {
		int d = i * LEVELTILESIZE * Cam::currentCam->zoom;
		if (-transform.position.x <= d ) {
			if (-transform.position.x + SDLClass::screenSizeX >= d) {
				FigureDrawer::DrawLineRef(Line(Vector2(d,0),Vector2(d,maxY)),c,transform);
				auto t = Text(std::to_string(i));
				t.camDependent = false;
				TextDrawer::DrawSimpleText(t, Vector2(transform.position.x + (d) + 5, 0),TextDrawer::ALIN_LEFT, TextDrawer::ALT_UP);
			}
		}
	}
	int maxX = LEVELSIZEX * LEVELTILESIZE * Cam::currentCam->zoom;
	for (int i = 1; i < LEVELSIZEY ; i++) {
		int d = i * LEVELTILESIZE * Cam::currentCam->zoom;
		if (-transform.position.y <= d) {
			if (-transform.position.y + SDLClass::screenSizeY >= d) {
				FigureDrawer::DrawLineRef(Line(Vector2(0, d), Vector2( maxX, d)), c,transform);
				auto t = Text(std::to_string(i));
				t.camDependent = false;
				TextDrawer::DrawSimpleText(t, Vector2(5,transform.position.y + (d)+5), TextDrawer::ALIN_LEFT, TextDrawer::ALT_UP);
			}
		}
	}
	

}

void LevelEditor::DrawPuttingObjectSelectedName() {
	std::string a = *ogSelected;
	TextDrawer::DrawSimpleText(Text(objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size() == 0 ? "NO ITEMS, PRESS I TO ADD":
		objectPlacer.globalPlaceableObjects[objectPlacer.currentBrushNumber][objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber][puttingObjectSelection]].name),
		Mouse::GetVector2Pos()+Vector2(0,-10));
	TextDrawer::DrawSimpleText(Text(*ogSelected,15,Color(255,0,0),"Arial"), Mouse::GetVector2Pos() + Vector2(0, -25));
}

void LevelEditor::NewLevel() {
	currentLevel = Level();
}

void LevelEditor::ClearLevelTemp() {
	
	objectPlacer.levelTemp.nWaves = &currentLevel.nWaves;
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			for (int k = 0; k < nLevelLayers; k++) {
				objectPlacer.levelTemp.levelLayers[k].level[i][j].first = &currentLevel.levelLayers[k].content[i][j];
				objectPlacer.levelTemp.levelLayers[k].level[i][j].second = nullptr;
				objectPlacer.levelTemp.levelLayers[k].baselayer[i] = objectPlacer.levelTemp.levelLayers[k].level[i];
			}
			for (int k = 0; k < nLevelWaves; k++) {
				objectPlacer.levelTemp.waves[k].level[i][j].first = &currentLevel.waves[k].content[i][j];
				objectPlacer.levelTemp.waves[k].level[i][j].second = nullptr;
				objectPlacer.levelTemp.waves[k].baselayer[i] = objectPlacer.levelTemp.waves[k].level[i];
			}
		}
	}
	
}

Vector2 LevelEditor::GetTileCoorFromWorldPos(Vector2 p) {
	return Vector2(int(p.x / LEVELTILESIZE) , int(p.y / LEVELTILESIZE) );
}



void LevelEditor::MovePuttingObjectSelection() {

	if (Keyboard::KeyboardCheck(SDL_SCANCODE_LALT)) {
		if (objectPlacer.currentWaveNumber < 1) {
			if (Mouse::scrollUp) {
				if (ogSelected == objectGroups.begin())
					ogSelected = objectGroups.end();
				ogSelected--;
				puttingObjectSelection = 0;
				if (objectPlacer.currentBrushNumber < 1)
					objectPlacer.currentBrushNumber = objectGroups.size();
				objectPlacer.currentBrushNumber--;
			}
			else if (Mouse::scrollDown) {
				ogSelected++;
				if (ogSelected == objectGroups.end())
					ogSelected = objectGroups.begin();
				puttingObjectSelection = 0;
				objectPlacer.currentBrushNumber++;
				if (objectPlacer.currentBrushNumber == objectGroups.size())
					objectPlacer.currentBrushNumber = 0;
			}
		}
	}
	else if (Mouse::scrollUp) {
		if (puttingObjectSelection == 0) {
			puttingObjectSelection = objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size();
		}
		puttingObjectSelection--;
	}
	else if (Mouse::scrollDown) {
		puttingObjectSelection++;
		if (puttingObjectSelection == objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size()) {
			puttingObjectSelection = 0;
		}
	}
}

void LevelEditor::PutObject(Vector2 coor) {

	if (objectPlacer.usedPlaceableObjects[objectPlacer.currentBrushNumber].size() > 0) {
		Vector2 tileCoor;
		if (coor == Vector2(-1, -1))
			tileCoor = GetTileCoorFromWorldPos(Mouse::GetVector2PosRef(&cam));
		else tileCoor = coor;
		std::pair<unsigned char*, PlaceableObject*>* tilePlace;
		if (objectPlacer.currentWaveNumber == 0)
			tilePlace = &objectPlacer.levelTemp.levelLayers[objectPlacer.GetCorrectLayer(objectPlacer.currentBrushNumber)].level[int(tileCoor.x)][int(tileCoor.y)];
		else
			tilePlace = &objectPlacer.levelTemp.waves[objectPlacer.currentWaveNumber - 1].level[int(tileCoor.x)][int(tileCoor.y)];
		if (*tilePlace->first != puttingObjectSelection) {
			if (*tilePlace->first != EMPTYTILEVALUE) {
				EraseObject();
			}
			if (PlaceableObject* p = objectPlacer.Place(puttingObjectSelection, objectPlacer.GetTilePosFromTileCoor(tileCoor))) {
				tilePlace->second = p;
				*tilePlace->first = puttingObjectSelection;
				if (tilePlace->second->hasSettings) {
					tilePlace->second->SetSettings();
				}
				if (tilePlace->second->needSecondPos) {
					tilePlace->second->SetSecondPos(objectPlacer.GetTilePosFromTileCoor(secondClick));
				}
				MadeChange();
				WriteConfig();

			}
		}
	}
}

void LevelEditor::EraseObject() {
	Vector2 tileCoor = GetTileCoorFromWorldPos(Mouse::GetVector2PosRef(&cam));
	std::pair<unsigned char*, PlaceableObject*>* tilePlace;
	if (objectPlacer.currentWaveNumber == 0)
		tilePlace = &objectPlacer.levelTemp.levelLayers[objectPlacer.GetCorrectLayer(objectPlacer.currentBrushNumber)].level[int(tileCoor.x)][int(tileCoor.y)];
	else
		tilePlace = &objectPlacer.levelTemp.waves[objectPlacer.currentWaveNumber - 1].level[int(tileCoor.x)][int(tileCoor.y)];

	if (*tilePlace->first != EMPTYTILEVALUE) {
		tilePlace->second->isActive = false;
		*tilePlace->first = EMPTYTILEVALUE;
		
		MadeChange();
		WriteConfig();
	}
}

