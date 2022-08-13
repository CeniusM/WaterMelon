
#include "GameOfChess.h"


SDL_Texture* playerTexture;
SDL_Rect srcR, destR;
SDLHelper sdlHelper;

void GameOfChess::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem has initilized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
			m_isRunning = true;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
	}
	else
		m_isRunning = false;


	//SDL_Surface* tmpSurface = IMG_Load("Assets/picture.png");
	//playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	//SDL_FreeSurface(tmpSurface);
	playerTexture = sdlHelper.LoadImage("Assets/n.bmp", renderer);
}

void GameOfChess::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;

	default:
		break;
	}
}

void GameOfChess::Update()
{
	m_Count++;
	destR.h = 100;
	destR.w = 100;
	destR.x = 100;
	destR.y = 100;


	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		int pos = (i*8)+j;
	//
	//		if (board.board[pos] == 0)
	//			continue;
	//
	//		SDL_Rect rect;
	//		rect.x = j * 100;
	//		rect.y = i * 100;
	//		rect.h = 100;
	//		rect.w = 100;
	//
	//		RenderPiece(&rect, sprites[board.board[pos]]);
	//	}
	//}


	//std::cout << m_Count << std::endl
}

void GameOfChess::Render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, playerTexture, NULL, &destR);

	SDL_RenderPresent(renderer);
}

void GameOfChess::CLean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// delete all textures
	SDL_DestroyTexture(playerTexture);



	SDL_Quit;
	std::cout << "finished cleanup\n";
}

bool GameOfChess::Running() { return m_isRunning; }

void GameOfChess::RenderPiece(SDL_Rect* rect, SDL_Texture* sprite)
{

}





GameOfChess::GameOfChess()
{
}

GameOfChess::~GameOfChess()
{
}