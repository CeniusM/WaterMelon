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
	UnsafeWaterMelon board;
	Move move(0, 0, 0);
	board.MakeMove(&move);

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





	SDL_Delay(5000);






	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//
	//for (int i = 0; i < 100; i++)
	//{
	//	Timer time;
	//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//
	//	SDL_RenderClear(renderer);
	//
	//	SDL_RenderPresent(renderer);
	//}
	//
	//{
	//	Timer time;
	//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//
	//	SDL_RenderClear(renderer);
	//
	//	SDL_RenderPresent(renderer);
	//}
	//
	//
	//
	//
	//SDL_Delay(5000);

	return 1;
}