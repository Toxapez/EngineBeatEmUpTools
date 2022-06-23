#include "Inventory.h"
Inventory Inventory::instance;
std::vector<Item**>  Inventory::itemsShownOrder;
std::vector<Item*> Inventory::heldItems;

Inventory::Inventory(){
	
	grind.color = Color(255);
	grind.size = Vector2(10,10);
	grind.cellSize = Vector2(50,50);
	transform.position = Vector2(-1000,-500);
	for (int i = 0; i < 3; i++) {
		sortButtons[i].transform.position.x = transform.position.x + grind.cellSize.x * grind.size.x ;
		sortButtons[i].transform.position.y = transform.position.y + sortButtons[0].size.y * i ;
		sortButtons[i].isActive = false;
	}
	inventorySize = 1;
	
	nHeldItems = 0;
	isActive = false;
}

void Inventory::LoadAllItem() {
	std::string n, t, des, dur;
	std::vector<std::string*> vars;

	vars.push_back(&n);
	vars.push_back(&t);
	vars.push_back(&des);
	vars.push_back(&dur);

	Reader::SetReader("assets/info/items/1.tsv", &vars);
	int i = 0;
	while (!Reader::IsFinished()) {
		Reader::Read();
		SpriteStatic* spr = new SpriteStatic();
		baseItems.push_back({i,std::stoi(t),n,des,std::stoi(dur),spr});
		spr->Set(std::string("items/" + std::to_string(i+1) + ".png"),Vector2(100,100));
		i++;
	}
}

void Inventory::AfterStaticStart() {
	AugmentInventorySize();
	LoadAllItem();
 	AddItem(1);
	AddItem(2);
	AddItem(3);
	AddItem(1);
	AddItem(1);
	AddItem(2);
	AddItem(3);
	AddItem(1);
	AddItem(1);
	AddItem(2);
	AddItem(3);
	AddItem(1);
	AddItem(1);
	AddItem(2);
	AddItem(3);
	AddItem(1);
	AddItem(4);
	AddItem(5);
	AddItem(6);
}

void  Inventory::AugmentInventorySize() {
	UpdateRealOrder();
	inventorySize *= 2;
	heldItems.reserve(inventorySize);
	RealOrder();
}

void Inventory::ItemsHeldChanged() {
	grind.size.y =  int(nHeldItems / grind.size.x) + 1;
}


void Inventory::AddItem(int ID) {
	nHeldItems++;

	if (nHeldItems > inventorySize)
		AugmentInventorySize();

	heldItems.push_back(new Item(&baseItems[ID-1],false));
	itemsShownOrder.push_back(&heldItems[heldItems.size()-1]);
	ItemsHeldChanged();
}

void Inventory::Update() {
	if (sortButtons[0].pressed)
		OrderItemsByName();
	if (sortButtons[1].pressed)
		OrderItemsByType();
	if (sortButtons[2].pressed)
		OrderItemsByDate();

	if (Keyboard::KeyboardPressed(SDL_SCANCODE_0))
		AddItem(0);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_1))
		AddItem(1);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_2))
		AddItem(2);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_3))
		AddItem(3);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_4))
		AddItem(4);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_5))
		AddItem(5);
	if (Keyboard::KeyboardPressed(SDL_SCANCODE_6))
		AddItem(6);
}

void Inventory::Draw(){
	grind.Draw(transform);
	auto gPositions = grind.GetCenteredPositions(transform);
	for (int i = 0; i < itemsShownOrder.size(); i++) {
		(*itemsShownOrder[i])->base->sprite->Draw(gPositions[i], true, 0,SDL_Rect(),grind.cellSize.x/100);
	}
}

void Inventory::RealOrder() {
	itemsShownOrder.clear();
	for (int i = 0; i < heldItems.size(); i++)
		itemsShownOrder.push_back(&heldItems[i]);
}

void Inventory::UpdateRealOrder() {
	std::vector<Item*> r;
	for (auto c : itemsShownOrder)
		r.push_back(*c);
	heldItems = r;
	RealOrder();
}

bool OrderByType(Item** i, Item** j) { return ((*i)->base->type < (*j)->base->type); }

std::vector<ItemSubGroup> AlphabeticOrderer::GetTypeGroups(int n, ItemSubGroup ig) {
	std::vector<Item**>::iterator c = ig.begin;
	std::vector<ItemSubGroup> r;
	while (c != ig.end) {
		int cTracking = (**c)->base->type;
		ItemSubGroup nISG;
		nISG.begin = c;
		while ((**c)->base->type == cTracking) {
			c++;
			if (c == ig.end) break;
		}
		nISG.end = c == ig.end ? ig.end : c;
		r.push_back(nISG);
	}
	return r;

}

void Inventory::OrderItemsByType() {
	RealOrder();
	std::sort(itemsShownOrder.begin(), itemsShownOrder.end(), OrderByType);
	AlphabeticOrderer::OrderSubGroups(0, AlphabeticOrderer::GetTypeGroups(0, { itemsShownOrder.begin(),itemsShownOrder.end() }));
}

bool OrderByName(Item** i, Item** j) { return int(((*i)->base->name.front()) < int((*j)->base->name.front())); }

void Inventory::OrderItemsByName() {
	RealOrder();
	std::sort(itemsShownOrder.begin(), itemsShownOrder.end(), OrderByName);
	AlphabeticOrderer::OrderSubGroups(1,AlphabeticOrderer::GetLetterGroups(0,{ itemsShownOrder.begin(),itemsShownOrder.end() }));
}



int AlphabeticOrderer::SubOrderByNameScope;
bool AlphabeticOrderer::SubOrderByName(Item** i, Item** j) { 
	return int(((*i)->base->name[SubOrderByNameScope]) < int((*j)->base->name[SubOrderByNameScope])); 
}

void AlphabeticOrderer::OrderSubGroups(int n, std::vector<ItemSubGroup > v) {
	for (auto c : v)
		if((++c.begin)-- != c.end)
			Inventory::SubOrderItemsByName(n, c);
}

int AlphabeticOrderer::ShorterNameInList(ItemSubGroup ig) {
	std::vector<Item**>::iterator c = ig.begin;
	Item** r = *ig.begin;
	while (c != ig.end) {
		if ((**c)->base->name.size() < (*r)->base->name.size())
			r = *c;
		c++;
	} 
	c--;
	return (**c)->base->name.size();
}

std::vector<ItemSubGroup> AlphabeticOrderer::GetLetterGroups(int n, ItemSubGroup ig) {
	std::vector<Item**>::iterator c = ig.begin;
	std::vector<ItemSubGroup> r;
	while (c != ig.end) {
		char cTracking = (**c)->base->name[n];
		ItemSubGroup nISG;
		nISG.begin = c;
		while ((**c)->base->name[n] == cTracking) {
			c++;
			if (c == ig.end) break;
		}
		nISG.end = c == ig.end ? ig.end : c;
		r.push_back(nISG);
	}
	return r;

}

void Inventory::SubOrderItemsByName(int n, ItemSubGroup ig) {
	if (AlphabeticOrderer::ShorterNameInList(ig) < n)
		return;
	AlphabeticOrderer::SubOrderByNameScope = n;
	std::sort(ig.begin, ig.end, AlphabeticOrderer::SubOrderByName);
	AlphabeticOrderer::OrderSubGroups(n+1, AlphabeticOrderer::GetLetterGroups(n,{ ig.begin,ig.end }));
}

std::vector<ItemSubGroup> AlphabeticOrderer::GetDateGroups(int n, ItemSubGroup ig) {
	std::vector<Item**>::iterator c = ig.begin;
	std::vector<ItemSubGroup> r;
	while (c != ig.end) {
		Date cTracking = (**c)->date;
		ItemSubGroup nISG;
		nISG.begin = c;
		while ((**c)->date == cTracking) {
			c++;
			if (c == ig.end) break;
		}
		nISG.end = c == ig.end ? ig.end : c;
		r.push_back(nISG);
	}
	return r;

}

bool OrderByDate(Item** i, Item** j) { 
	return ((*i)->date < (*j)->date); 
}
void Inventory::OrderItemsByDate() {
	RealOrder();
	std::sort(itemsShownOrder.begin(), itemsShownOrder.end(), OrderByDate);
	AlphabeticOrderer::OrderSubGroups(0, AlphabeticOrderer::GetDateGroups(0, { itemsShownOrder.begin(),itemsShownOrder.end() }));
}