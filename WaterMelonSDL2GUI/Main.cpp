#include <chrono>
#include <iostream>

#include "include/SDL.h"
#include "../WaterMelonEngine/Timer.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.h"

#undef main

int main()
{

	for (int i = 0; i < 1000; i++)
	{
		bool p = (((0b1111111111111111111111 << 5) & 0x8000000000000000) == 0x8000000000000000);
	}

	{
		Timer timer;
		for (int i = 0; i < 10000000; i++)
		{
			bool p = (((0b1111111111111111111111 << 4) & 0x8000000000000000) == 0x8000000000000000);
		}
	}





	//SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//
	//
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
	//SDL_Delay(5000);

	return 1;
}