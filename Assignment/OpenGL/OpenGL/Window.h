#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

class Window
{
public:
	Window();
	~Window();

	bool isRunning() const {
		return running;
	}

	void setRunning(bool value) {
		running = value;
	}

	SDL_Window* getWindow() const {
		return window;
	}

private:
	bool running;
	SDL_Window* window;
	SDL_GLContext context;
};