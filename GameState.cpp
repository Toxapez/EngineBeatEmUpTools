#include "GameState.h"
Scoper50<GameState*> GameState::gamestates;
GameState* GameState::currentGameState;

GameState::GameState() {
	gamestates.GetNextScope() = this;
}

void GameState::AfterStaticStart() {
	for (int i = 0; i < gamestates.placerScope; i++) 
		gamestates[i]->SetActive(false);
}

void GameState::ChangeGameState(GameState* g) {
	if (currentGameState)
		currentGameState->SetActive(false);
	currentGameState = g;
	g->SetActive(true);
}