#include "Window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window::Window() 
	: running (true)
{
	window = SDL_CreateWindow ("OpenGL 3D Game", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
