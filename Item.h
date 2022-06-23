#pragma once
#include <string>
#include "SpriteStatic.h"
#include "Date.h"

struct BaseItem {
	int ID;
	int type;
	std::string name;
	std::string description;
	int durability;
	SpriteStatic* sprite;
};



struct Item
{
	BaseItem* base;
	bool isComplex = false;
	Date date;
	Item(BaseItem* b, bool ic) {
		base = b;
		isComplex = ic;
		date = Date::GetCurrent();
	}

	
};

class ItemComplex : public Item
{
	int durability;
};