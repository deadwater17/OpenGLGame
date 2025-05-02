#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "uiShader.h"

class Score 
{
public:
    Score();
    ~Score();

    void update(int amount);
    void draw(const uiShader* uishader);

private:
    int m_score;
    int width, height;
    std::string text;
    GLuint m_texture;
    TTF_Font* m_font;

    void updateTexture(); 
};