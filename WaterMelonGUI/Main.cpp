#include <chrono>
#include <iostream>

#include "SDL.h"
#include "GameOfChess.h"
#include "Timer.h"
//#include "../WaterMelon/Timer.h"


#undef main

int main()
{
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