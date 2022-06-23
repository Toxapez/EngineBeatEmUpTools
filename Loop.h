#pragma once
#include "FrameController.h"
#include "ObjectManager.h"
#include "GameSystems.h"
#include "FigureDrawer.h"
#include "Mouse.h"
#include "Animation.h"
#include "InputManager.h"
#include "LevelEditor.h"
#include "OpenGLClass.h"
#include "SpriteStatic.h"
#include "GlobalStaticVariables.h"
class Loop
{
	static void FirstUpdate();
	static void Update();
	static void LateUpdate();

public:
	static void Start();
	static bool Looping();
	static void Finish();
};






