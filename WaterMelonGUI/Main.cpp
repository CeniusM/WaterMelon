#include <chrono>
#include <iostream>

#include "SDL.h"
#include "GameOfChess.h"
#include "Perft.h"
#include "Timer.h"
//#include "../WaterMelon/Timer.h"

#undef main

void PerftTest()
{
	PerftRunner perftRunner{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

	std::cout << perftRunner.BulkSearch(4);


	std::cout << "\n";
}

int main()
{
	//PerftTest();
	//return 0;
	/*int start = 0;
	Bitboard some = 124123;
	Square pos = 32;

	bool b = (DotBiboards[pos] & some) == 0;

	bool a = ((some >> pos) & SignificantBit) == SignificantBit;

	int end = 0;*/

	//std::cout << sizeof(UnsafeWaterMelon) << "\n";


	// --Testing above --

	//const int RestingFPS = 20;
	//const int DragingFPS = 144;
	//const int FPS = 30; // for debuging
	const int FPS = 142; // makes it go from 144=6,9... 142=7
	int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	GameOfChess game;
	game.Init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	game.Render();

	while (game.Running())
	{
		//Timer timer;
		frameStart = SDL_GetTicks();

		{
			game.HandleEvents();
			game.Update();

			// used to indicate if fx, an ai have moved, the player have clicked setting, or moved and so on
			if (game.SomethingHappend)
			{
				game.Render();
			}
		}

		//if (game.IsDraging())
		//	FPS = DragingFPS;
		//else
		//	FPS = RestingFPS;
		//frameDelay = 1000 / FPS;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	game.Clean();

	return 1;
}