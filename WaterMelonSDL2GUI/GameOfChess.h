#pragma once

#include <iostream>

#include "include/SDL.h"

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
	SDL_Window* window;
	SDL_Renderer* renderer;

};

GameOfChess::GameOfChess()
{
}

GameOfChess::~GameOfChess()
{
}