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

    void increaseScore(int amount);
    void draw(uiShader& uishader);

    int getScore() const { return m_score; }

private:
    int m_score;
    int m_width, m_height;
    std::string text;
    GLuint m_texture;
    TTF_Font* m_font;
    GLuint quadVAO, quadVBO;

    void setupQuad();
    void updateTexture(const std::string& newText);
};