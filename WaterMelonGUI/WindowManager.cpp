#include "WindowManager.hpp"


WindowManager::WindowManager(char* title, int width, int height)
{
	SetTitle(title);
	TryInitSize(width, height);
}

WindowManager::~WindowManager()
{
	Destroy();
}

void WindowManager::SetTitle(char* title)
{
	Title = title;
	if (HasInit)
		SDL_SetWindowTitle(window, title);
}

bool WindowManager::TryPopEvent(SDL_Event* event)
{
	int succes = SDL_PollEvent(event);
	return succes;
}

bool WindowManager::TryResizeWindow(int width, int height)
{
	Destroy();
	HasInit = TryInitSize(width, height);
	return HasInit;
}

SDL_Window* WindowManager::GetWindow()
{
	if (!HasInit)
		return nullptr;
	return window;
}

SDL_Renderer* WindowManager::GetRenderer()
{
	if (!HasInit)
		return nullptr;
	return renderer;
}

const char* WindowManager::GetTitle()
{
	return Title;
}

int WindowManager::GetWidth()
{
	return Width;
}

int WindowManager::GetHeight()
{
	return Height;
}

bool WindowManager::GetHasInit()
{
	return HasInit;
}

bool WindowManager::TryInitSize(int width, int height)
{
	if (HasInit)
		Destroy();
		//ThrowException("Can't Init size of allready initilized WindowManager");
	
	Width = width;
	Height = height;

	SDL_CreateWindow(Title, 0, 0, width, height, 0);

	return true;
}

void WindowManager::Destroy()
{
	if (!HasInit)
		return;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	HasInit = false;
}
