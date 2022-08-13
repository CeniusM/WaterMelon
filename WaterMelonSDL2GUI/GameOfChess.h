#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDLHelper.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.cpp"

class GameOfChess
{
public:
	GameOfChess();
	~GameOfChess();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	void Render();
	void CLean();

	bool Running();

private:
	void RenderPiece(SDL_Rect* rect, SDL_Texture* sprite);

	UnsafeWaterMelon board;
	
	bool m_isRunning;
	int m_Count;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* sprites[24]; // black queen is at index 23
};