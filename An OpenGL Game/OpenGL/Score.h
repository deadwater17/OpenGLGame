#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <string>

#include "UIShader.h"

class Score 
{
public:
    Score();
    ~Score();

    void update(int amount);
    void draw(GLuint shaderID, int windowWidth, int windowHeight);

private:
    int m_score;
    GLuint m_vao, m_vbo;
    GLuint m_texture;
    TTF_Font* m_font;

    void initQuad();
    void updateTexture(); // Called when score changes
};