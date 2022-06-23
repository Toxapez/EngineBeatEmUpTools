#pragma once
#include <vector>
#include "Item.h"
#include "GameObject.h"
#include "Reader.h"
#include "Grind.h"
#include "SpriteStatic.h"
#include "Button.h"

struct ItemSubGroup {
	std::vector<Item**>::iterator begin;
	std::vector<Item**>::iterator end;
};

class Inventory : public GameObject
{
	static Inventory instance;
	std::vector<BaseItem> baseItems;
	
	Button sortButtons[3];
	Inventory();
	void LoadAllItem();
	void AddItem(int ID);
	void UpdateRealOrder();
	void RealOrder();
	void OrderItemsByType();
	void OrderItemsByName();
	void OrderItemsByDate();
	void Update();
	void Draw();
	Grind grind;
	void AfterStaticStart();
	int inventorySize;
	int nHeldItems;
	void AugmentInventorySize();
	void ItemsHeldChanged();
public:
	static std::vector<Item**> itemsShownOrder;
	static std::vector<Item*> heldItems;
	static void SubOrderItemsByName(int n, ItemSubGroup ig);
	
};

struct AlphabeticOrderer {
	static int SubOrderByNameScope;
	static bool SubOrderByName(Item** i, Item** j);
	static int ShorterNameInList(ItemSubGroup);
	static std::vector<ItemSubGroup > GetLetterGroups(int n, ItemSubGroup ig);
	static std::vector<ItemSubGroup > GetTypeGroups(int n, ItemSubGroup ig);
	static std::vector<ItemSubGroup > GetDateGroups(int n, ItemSubGroup ig);
	static void OrderSubGroups(int n, std::vector<ItemSubGroup > );
};