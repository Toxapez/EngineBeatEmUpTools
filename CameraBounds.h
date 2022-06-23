#pragma once
#include "RectTwoPoint.h"
struct CameraBounds
{
	RectTwoPoint rect;
	CameraBounds() {}
	CameraBounds(RectTwoPoint rect) : rect(rect) {

	}
};

