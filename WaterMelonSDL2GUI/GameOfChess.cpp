#include "GameOfChess.h"

void GameOfChess::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystem has initilized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);

		if (window)
		{
			std::cout << "window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
	}
}

void GameOfChess::HandleEvents()
{
}

void GameOfChess::Update()
{
}

void GameOfChess::Render()
{
}

void GameOfChess::CLean()
{
}

bool GameOfChess::Running() { return m_isRunning; }

