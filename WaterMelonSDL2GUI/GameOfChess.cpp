
#include "GameOfChess.h"


SDL_Texture* playerTexture;
SDL_Rect srcR, destR;
SDLHelper sdlHelper;

//SDL_Texture* LoadImage(std::string file, SDL_Renderer* r)
//{
//	SDL_Surface* loadedImage = nullptr;
//	SDL_Texture* texture = nullptr;
//	loadedImage = SDL_LoadBMP(file.c_str());
//
//	if (loadedImage != nullptr)
//	{
//		texture = SDL_CreateTextureFromSurface(r, loadedImage);
//		SDL_FreeSurface(loadedImage);
//	}
//	else
//		std::cout << SDL_GetError() << std::endl;
//	return texture;
//}

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



GameOfChess::GameOfChess()
{
}

GameOfChess::~GameOfChess()
{
}