#include "NewPlaceableObjectsCreator.h"

bool NewPlaceableObjectsCreator::BGItem(std::string n, std::string dir, Vector2 os) {
	BGItems::CreateNew(n, dir, os);
	LevelEditor::instance.objectPlacer.AddNewBGItem();
	return true;
}
