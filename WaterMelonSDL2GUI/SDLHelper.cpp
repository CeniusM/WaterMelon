
#include "SDLHelper.h"


SDL_Texture* SDLHelper::LoadImage(std::string file, SDL_Renderer* r)
{
	SDL_Surface* loadedImage = nullptr;
	SDL_Texture* texture = nullptr;
	loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(r, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		std::cout << SDL_GetError() << std::endl;
	return texture;
}

SDLHelper::SDLHelper()
{
}

SDLHelper::~SDLHelper()
{
}
