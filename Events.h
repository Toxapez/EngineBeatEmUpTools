#pragma once
#include "GameObject.h"

struct Event
{
	bool happen;
	bool happened;
	static std::vector<Event*> events;
	Event() {
		events.push_back(this);
	}
};



class Events : public GameObject
{
	void Update();
public:
	static Events instance;
	Event throwObject;
	Event enemiesOnScreen;
	Event punchEnemie;
};

