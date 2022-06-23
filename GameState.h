#pragma once
#include "GameObject.h"

struct GameState : public GameObject
{
	static Scoper50<GameState*> gamestates;
	GameState();
	void virtual SetActive(bool b) = 0;
	static GameState* currentGameState;
	static void ChangeGameState(GameState* g);
	void AfterStaticStart() override;
};

