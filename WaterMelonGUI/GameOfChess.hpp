#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDLHelper.hpp"
#include "SafeWaterMelon.hpp"
#include "UnsafeWaterMelonComparerer.hpp"
#include "Perft.hpp"
#include "Evaluator.hpp"

class GameOfChess
{
public:
	GameOfChess();
	~GameOfChess();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool IsDraging() { return MouseDraging; }
	bool Running();

	void LoadMoves(bool onlyAttacks = false);

	bool SomethingHappend = false;

private:
	bool NeedToRender = false; // used later so that if nothing is happening it wont need to render

	void RenderBackGround();
	void RenderPossibleMoves();
	// the int is if the player is draging a piece
	void RenderAllPieces(int PieceToLeaveOut = -1);
	void RenderPiece(SDL_Rect* rect, SDL_Texture* sprite);

	//SafeWaterMelon board = SafeWaterMelon();
	//SafeWaterMelon board = SafeWaterMelon("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("rnbqkbnr/ppp2p2/8/8/p4p1p/3pP3/PPPP1PPP/RNBQKBNR w KQkq - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("k7/4r2q/8/3PPB2/1r1PK3/8/1P6/b7 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("8/kp1R4/1p5r/2B1b3/8/7P/6PK/8 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("6q1/kp1R4/1p2n2r/2B1b3/8/4N2P/6PK/1Q6 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("n2bqkn1/2q5/q3q1q1/8/5q2/3q4/1q5K/8 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("8/8/8/8/2KP1rk1/8/8/8 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("8/8/3N4/8/2K2rk1/4P3/8/8 w - - 0 1");
	//SafeWaterMelon board = SafeWaterMelon("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
	//SafeWaterMelon board = SafeWaterMelon("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	SafeWaterMelon board = SafeWaterMelon("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
	//SafeWaterMelon board = SafeWaterMelon("");
	//SafeWaterMelon board = SafeWaterMelon("");
	//SafeWaterMelon board = SafeWaterMelon("");


	bool m_isRunning;
	long m_Count;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* sprites[24]; // black queen is at index 23


	int xMousePos = 0;
	int yMousePos = 0;
	bool pieceHaveBeenPicked;
	bool m_IsPieceBeingDraged;
	int m_PieceTypeBeingDraged;
	int m_piecePickedIndex;
	bool MouseDraging = false;

	//PerftRunner debug_Perft{ "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };
	PerftRunner debug_Perft{ };
	int debug_Depth = 4;
};