#include "WaveController.h"
WaveController WaveController::instance;

void WaveController::Update() {
	if (!LevelEditor::instance.editting) {
		if (LevelState::instance.wavesActive) {
			ObjectPlacer* ob = &LevelEditor::instance.objectPlacer;
			if (LevelState::instance.currentWave < *ob->levelTemp.nWaves) {
				if (LevelState::instance.nEnemies == 0) {
					for (int i = 0; i < LEVELSIZEY; i++) {
						for (int j = 0; j < LEVELSIZEX; j++) {
							int ID = LevelEditor::instance.currentLevel.waves[LevelState::instance.currentWave].content[i][j];
							if (ID != EMPTYTILEVALUE) {
								PlaceableObject* p = ob->placeableObjectsLists[0][ID].list->GetPlaceableObject(true);
								p->Set(ob->GetTilePosFromTileCoor(Vector2(i, j)), ID);
								p->spawnSquashCounter = 2;
								ob->levelTemp.waves[LevelState::instance.currentWave].baselayer[i][j].second = p;
							}
						}
					}
					LevelState::instance.currentWave++;
					LevelEditor::instance.UpdateConfig();
					LevelEditor::instance.objectPlacer.levelTemp.waves[LevelState::instance.currentWave].baselayer;
					LevelState::instance.maxEnemies = LevelState::instance.nEnemies;
				}
			}
			else {
				Audio::instance.music.engine->setAllSoundsPaused();
				LevelState::instance.wavesActive = false;
				
			}
		}
	}
}


void WaveController::Draw() {
	if (!LevelEditor::instance.editting) {
		//FigureDrawer::DrawFillRect(Rect(200, 70), Color(0, 0, 200));
		//TextDrawer::DrawText(Text("N.Enemies: " + std::to_string(LevelState::instance.nEnemies), 15, Color(255), "arial"), Vector2(10, 10));
		
		
	}
}