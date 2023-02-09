#pragma once

typedef int GameState;

enum GameStates
{
	Running = 2,
	WhiteWon = 1,
	Draw = 0,
	BlackWon = -1,
};