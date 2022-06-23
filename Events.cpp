#include "Events.h"
std::vector<Event*> Event::events;

Events Events::instance;

void Events::Update() {
	for (auto c : Event::events) {
		if (c->happen)
			c->happen = false;
		if (c->happened) {
			c->happen = true;
			c->happened = false;
		}
	}
}