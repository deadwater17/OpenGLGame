#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class GUI 
{
public:
    GUI();
    ~GUI();

    void init();               
    void draw(Shader& guiShader); 

private:
    unsigned int m_vao, m_vbo;
};