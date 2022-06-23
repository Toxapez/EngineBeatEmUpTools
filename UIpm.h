#pragma once
#include "GameObject.h"
#include "Player.h"
#include "SpriteStatic.h"
#include "PlayerVariables.h"
#include "LevelState.h"

struct Timer {
	float time;
	bool active;
	Timer() {};
	Timer(float t) {
		time = t;
		active = false;
	}
	
};

struct TimeLineEvents {
	std::vector<Timer> events;
	float counter;
	int activeEvent;
	void Reset() {
		Deactive();
		activeEvent = 0;
		events[activeEvent].active = true;
	}
	void NextEvent() {
		events[activeEvent].active = false;
		activeEvent++;
		if (isActive())
			events[activeEvent].active = true;
		else
			Deactive();
	}
	void Run() {
		counter += Kang::gameTimeSpeed;
		if (counter >= events[activeEvent].time) {
			counter -= events[activeEvent].time;
			NextEvent();
		}
	}

	float Percentage() {
		return counter / events[activeEvent].time;
	}
	bool isActive(){
		return activeEvent < events.size();
	}
	void Deactive() {
		if (isActive())
			events[activeEvent].active = false;
		activeEvent = events.size();
	}
};

class UIpm : public GameObject
{
	static UIpm instance;
	void AfterStaticStart();
	void Draw();
	SpriteStatic barra, killcount, itemBox, itemNameBox, flecha, dinero, spawnermasuno;
	float spawnermasunoCounter;
	float preEnemies;
	bool showingItemInfo;
	Vector2 titleOffset;
	UIpm();
	TimeLineEvents titleTimeline;
	RecolectableInfo titleObject;
};

