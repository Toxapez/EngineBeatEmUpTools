#pragma once
#include <future>  
#include "Vector2.h"
#include "SDLClass.h"
#include "Cam.h"
#include <utility>
#include "Keyboard.h"
class Mouse
{
	static int asyncWheelY;
	static std::pair<int, int> pos;
public:
	static bool leftClickCheck;
	static bool leftClickPressed;
	static bool rightClickCheck;
	static bool rightClickPressed;
	static bool scrollUp;
	static bool scrollDown;
	static Vector2 GetVector2Pos();
	static Vector2 GetVector2PosRef(Cam* c);
	static void Start();
	static void Update();
	static void ScrollDetection();
	static bool isFileDropped;
	static std::string fileDroppedDir;
	static void LateUpdate();
	
};

