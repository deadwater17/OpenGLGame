#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

SDL_Texture* renderText(const std::string& message, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
