#include "Score.h"
/*
const GLfloat quadVertices[] = {
    0.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 0.0f,

    0.0f, 1.0f,   0.0f, 1.0f,
    1.0f, 0.0f,   1.0f, 0.0f,
    1.0f, 1.0f,   1.0f, 1.0f
};
*/
Score::Score() 
    : m_score(0)
    , m_texture(0)
    , m_font(nullptr) 
    , score_width(NULL)
    , score_height(NULL)
{

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }

    m_font = TTF_OpenFont("ShineTypewriter-lgwzd.ttf", 48); 
    if (!m_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }


	updateTexture("Score: 0");
}

Score::~Score() {
    if (m_texture) glDeleteTextures(1, &m_texture);
    if (m_font) TTF_CloseFont(m_font);
    TTF_Quit();
}

void Score::increaseScore(int amount) 
{
    m_score += amount;
    updateTexture("Sore: " + std::to_string(m_score));
}

void Score::updateTexture(const std::string& newText) 
{
    text = newText;

    SDL_Color color = { 255, 255, 255, 255 }; // white

    SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), color);
    if (!surface) 
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }

    score_width = surface->w;
	score_height = surface->h;

    if (m_texture) glDeleteTextures(1, &m_texture);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);
}

void Score::setupQuad()
{
    float quadVertices[] = {
        // positions     // texCoords
        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 0.0f,      0.0f, 0.0f,

        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f
    };

    // Create and bind VAO/VBO for the quad
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Score::draw(uiShader& uishader) 
{
    glBindTexture(GL_TEXTURE_2D, m_texture);

    if (!quadVAO)
    {
        setupQuad();
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

