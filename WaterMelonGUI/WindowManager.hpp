#pragma once

#include "SDL.h"
#include "ThrowHelper.hpp"

static class WindowManager
{
public:
	WindowManager(char* title, int width, int height);
	~WindowManager();

	void SetTitle(char* title);
	bool TryPopEvent(SDL_Event* event);
	bool TryResizeWindow(int width, int height);

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	const char* GetTitle();
	int GetWidth();
	int GetHeight();
	bool GetHasInit();

private:

	bool TryInitSize(int width, int height);
	void Destroy();

	bool HasInit = false;

	int Width = 0;
	int Height = 0;

	char* Title = nullptr;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};