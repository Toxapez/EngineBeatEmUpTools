#pragma once
#include <iostream>
#include "SDLClass.h"
class FrameController
{
	static const int FPS;
	static const int frameDelay;
	static Uint32 framestart;
	static int frametime;
public:
	static void FirstUpdate();
	static void LateUpdate();
};


