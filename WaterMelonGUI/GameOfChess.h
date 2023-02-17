#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDLHelper.h"
#include "SafeWaterMelon.h"

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

	bool SomethingHappend = false;

private:
	bool NeedToRender = false; // used later so that if nothing is happening it wont need to render

	void RenderBackGround();
	void RenderPossibleMoves();
	// the int is if the player is draging a piece
	void RenderAllPieces(int PieceToLeaveOut = -1);
	void RenderPiece(SDL_Rect* rect, SDL_Texture* sprite);

	SafeWaterMelon board = SafeWaterMelon();
	//SafeWaterMelon board = SafeWaterMelon("k7/4r2q/8/3PPB2/1r1PK3/8/1P6/b7 w - - 0 1");
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
};