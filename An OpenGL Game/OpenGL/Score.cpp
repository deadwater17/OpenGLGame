#include "Score.h"



const GLfloat quadVertices[] = {
    //  X     Y       U     V
    0.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 0.0f,

    0.0f, 1.0f,   0.0f, 1.0f,
    1.0f, 0.0f,   1.0f, 0.0f,
    1.0f, 1.0f,   1.0f, 1.0f
};

Score::Score() 
    : m_score(0)
    , m_texture(0)
    , m_font(nullptr) 
{

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }

    m_font = TTF_OpenFont("ShineTypewriter-lgwzd.ttf", 28); 
    if (!m_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

}

Score::~Score() {
    if (m_texture) glDeleteTextures(1, &m_texture);
    if (m_font) TTF_CloseFont(m_font);
    TTF_Quit();
}

void Score::update(int amount) {
    m_score += amount;
    updateTexture();
}

void Score::updateTexture(const std::string& newText) 
{
    text = newText;

    SDL_Color color = { 255, 255, 255, 255 }; // white

    SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }

    width = surface->w;
	height = surface->h;

    if (m_texture) glDeleteTextures(1, &m_texture);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
}

void Score::draw(const uiShader* uishader) 
{

    glBindTexture(GL_TEXTURE_2D, textureId);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "u_Model"), 1, GL_FALSE, glm::value_ptr(model));

    // Bind VAO/VBO for your quad (e.g., two triangles making a rectangle)
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}