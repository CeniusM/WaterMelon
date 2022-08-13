#pragma once

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"



class SDLHelper
{
public:
	SDLHelper();
	~SDLHelper();

	SDL_Texture* LoadImage(std::string file, SDL_Renderer* r);
private:

};