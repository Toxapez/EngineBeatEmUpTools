#include "ChooseGrind.h"

ChooseGrind::ChooseGrind() {
	nOptions = 1;
	optionHeld = 1;
}

ChooseGrind::ChooseGrind(int i) {
	nOptions = i;
	optionHeld = 1;
}

void ChooseGrind::Forward() {
	optionHeld++;
	if (optionHeld > nOptions) {
		optionHeld = 1;
	}
}

void ChooseGrind::Backward() {
	optionHeld--;
	if (optionHeld == 0) {
		optionHeld = nOptions;
	}
}