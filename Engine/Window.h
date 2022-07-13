#pragma once

#include "SDL.h"

class Window
{
public:
	Window(int width, int height);

	~Window();

	void evPoll(SDL_Event &event);

	static SDL_Window* window;

	void SwapBuffers();

	static int width;

	static int height;

	static bool onUI;

	static bool isClose;

	void Clear();

	int WinInit();
private:

	SDL_GLContext glcontext;
};