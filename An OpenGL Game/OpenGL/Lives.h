#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>

#include "uiShader.h"

class Lives
{
public:
    Lives();
    ~Lives();

    void decreaseLives(int amount);
    void draw(uiShader& uishader);

    int getLives() const { return m_lives; }

    int getWidth() const { return lives_width; }
    int getHeight() const { return lives_height; }

    int m_lives;
private:


    int lives_width, lives_height;

    std::string text;
    GLuint m_texture;
    TTF_Font* m_font;
    GLuint quadVAO, quadVBO;

    void setupQuad();
    void updateIMG(const std::string& newText);
    void updateTextureFromIMG(const std::string& imagePath);
};
