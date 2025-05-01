#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"

#include "World.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{
    SDL_Window* window = SDL_CreateWindow("OpenGL Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!SDL_GL_CreateContext(window))
    {
        throw std::runtime_error("Failed to create OpenGL context");
    }

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialze GLEW");
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }

    World world(window, renderer);
    const Uint8* keyboard = nullptr;

	bool quit = false;
    SDL_Event event;
    float lastTime = SDL_GetTicks() / 1000.0f;

	while (!quit)
	{
        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

		SDL_Event ev = { 0 };
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = true;
			}
		}
        SDL_PumpEvents();                      
        keyboard = SDL_GetKeyboardState(nullptr);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        world.update(deltaTime, keyboard);
        world.render();

        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

		SDL_GL_SwapWindow(window);
	}

    SDL_RenderClear(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}