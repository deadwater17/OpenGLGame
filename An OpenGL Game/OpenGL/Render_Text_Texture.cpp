#include "Render_Text_Texture.h"

// Render text to the screen
SDL_Texture* renderText(const std::string& message, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer)
{
    SDL_Surface* surf = TTF_RenderText_Solid(font, message.c_str(), color);
    if (surf == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);
    return texture;
}
