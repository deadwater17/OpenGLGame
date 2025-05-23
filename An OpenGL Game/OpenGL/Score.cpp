#include "Score.h"

Score::Score() 
    : m_score(0)
    , m_texture(0)
    , m_font(nullptr) 
    , score_width(NULL)
    , score_height(NULL)
{

    if (TTF_Init() == -1) {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }

    m_font = TTF_OpenFont("ShineTypewriter-lgwzd.ttf", 48); 
    if (!m_font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    
    updateTexture("Score: 0");      // sets score as 0 when initialised
    updateTextureFromImage("Score.png");        // puts the png on the quad
}

Score::~Score() {
    if (m_texture) glDeleteTextures(1, &m_texture);
    if (m_font) TTF_CloseFont(m_font);
    TTF_Quit();
}

void Score::increaseScore(int amount) 
{
    m_score += amount;
	std::string scoreText = "Score: " + std::to_string(m_score);
    updateTexture(scoreText);
	std::cout << scoreText << std::endl;
    updateTextureFromImage("Score.png");
}

void Score::updateTexture(const std::string& newText)       // craetes a score png
{
    text = newText;

    SDL_Color color = { 255, 255, 255, 255 };

    SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    if (!surface)
    {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }

    std::cout << "Surface created. Size: " << surface->w << " x " << surface->h << std::endl;

    // Save to PNG file
    if (IMG_SavePNG(surface, "Score.png") != 0) {
        std::cout << "Failed to save PNG: " << IMG_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
}

void Score::updateTextureFromImage(const std::string& imagePath)        // displays the score png texture in the quad
{
    SDL_Surface* img = IMG_Load(imagePath.c_str());
    if (!img)
    {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    score_width = img->w;
    score_height = img->h;

    if (m_texture) glDeleteTextures(1, &m_texture);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    SDL_FreeSurface(img);

    if (quadVAO) {
        glDeleteVertexArrays(1, &quadVAO);
        quadVAO = 0;
    }
    if (quadVBO) {
        glDeleteBuffers(1, &quadVBO);
        quadVBO = 0;
    }
    setupQuad();
}



void Score::setupQuad()     // creation of the quad to match the png axis to the quad
{
    float w = static_cast<float>(score_width);
    float h = static_cast<float>(score_height);

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    if (!quadVAO)       // if don't have quad is null, it rebuld the quad again
    {
        std::cout << "Rebuilding quad" << std::endl;
        setupQuad();
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

