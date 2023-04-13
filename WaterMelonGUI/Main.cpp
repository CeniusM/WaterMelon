#include <chrono>
#include <iostream>

#include "SDL.h"
#include "Memcompare.hpp"
#include "UnsafeWaterMelonComparerer.hpp"
#include "GameOfChess.hpp"
#include "Perft.hpp"
#include "Timer.hpp"
#include "ThreadPool.hpp"
//#include "../WaterMelon/Timer.hpp"

#undef main

void RunTime(std::string fen, int depth)
{
	UnsafeWaterMelon b{ fen };
	PerftRunner perftRunner1{};
	auto start = std::chrono::high_resolution_clock::now();
	long long count = perftRunner1.BulkSearch(&b, depth);
	auto finish = std::chrono::high_resolution_clock::now();
	long long time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

	std::cout << std::to_string(depth) + " Count: " << std::to_string(count) << " Nps: " << std::to_string((count * 1000) / time) << "\n";
}

void PerftTest()
{
	std::cout << "Note: Test this with graphics so you can see where its goes wrong \n";

	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 1);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 2);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 3);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 4);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 5);
	return;
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6);
	RunTime("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 7);


	//PerftRunner perftRunner{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
	//perftRunner.BulkSearchLog(5);
	//perftRunner.BulkSearchLog(6);

	std::cout << "\n";
}

void Hello()
{
	std::cout << "Hello\n";
}

void HelloWorld()
{
	std::cout << "Hello World\n";
}

void World()
{
	std::cout << "World\n";
}

int main()
{
	std::cout << "UnsafeBoard in bytes: " << sizeof(UnsafeWaterMelon) << "\n";
	std::cout << "BoardState in bytes: " << sizeof(BoardState) << "\n";
	//Logger::LogBitboard(BitboardFromSquare(59) | BitboardFromSquare(58) | BitboardFromSquare(57));
	//Logger::Log(std::to_string(BitboardFromSquare(59) | BitboardFromSquare(58) | BitboardFromSquare(57)));
	//return 0;

	srand(312345654);

	//ThreadPool pool{2};
	//pool.StartTask(&Hello);
	//pool.StartTask(&HelloWorld);
	//pool.StartTask(&World);
	//return 0;

	//UnsafeWaterMelon obj1;
	//void* temp = nullptr;
	//while (temp == nullptr)
	//	temp = malloc(256 * sizeof(Move));
	//obj1.GetPossibleMoves((Move*)temp, false, false);
	//char* obj1Save = nullptr;
	//while (obj1Save == nullptr)
	//	obj1Save = (char*)malloc(sizeof(obj1));

	//for (size_t i = 0; i < sizeof(UnsafeWaterMelon); i++)
	//	obj1Save[i] = ((char*)&obj1)[i];

	//bool* result = MemCopare(sizeof(UnsafeWaterMelon), &obj1, (void*)obj1Save);
	//std::cout << "Size of UnsafeWaterMelon" << sizeof(UnsafeWaterMelon) << "\n";
	//for (size_t i = 0; i < sizeof(UnsafeWaterMelon); i++)
	//{
	//	std::cout << result[i];
	//}

	//obj1.MakeMove(CreateMove(56, 56 - 8, 0));
	//obj1.UnMakeMove();
	//obj1.GetPossibleMoves((Move*)temp, false, false);
	//result = MemCopare(sizeof(UnsafeWaterMelon), &obj1, (void*)obj1Save);
	//std::cout << "\n\n\n\n";
	//for (size_t i = 0; i < sizeof(UnsafeWaterMelon); i++)
	//{
	//	std::cout << result[i];
	//}

	//UnsafeWaterMelon mel1{};
	//UnsafeWaterMelon mel2{};
	////CompareWaterMelons(&mel1, &mel2);
	//mel1.MakeMove(CreateMove(8, 8 + 16, PawnDoubleForward));
	//mel1.UnMakeMove();
	//CompareWaterMelons(&mel1, &mel2);
	//return 0;


	//std::cout << sizeof(BoardState);
	//return 0;

	PerftTest();
	//PerftRunner perft{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
	//perft.BulkSearchLog(4);

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