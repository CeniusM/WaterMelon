#pragma once

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDLHelper.h"

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
	bool m_isRunning;
	int m_Count;
	SDL_Window* window;
	SDL_Renderer* renderer;

};