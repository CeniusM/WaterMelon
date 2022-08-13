#include <chrono>
#include <iostream>

#include "SDL.h"
#include "GameOfChess.h"
#include "../WaterMelonEngine/Timer.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.cpp"

#undef main

int main()
{
	GameOfChess game;
	game.Init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	game.Render();

	while (game.Running())
	{
		Timer timer;
		game.HandleEvents();
		game.Update();
		game.Render();
	}
	game.CLean();

	return 1;
}