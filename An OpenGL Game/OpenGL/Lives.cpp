#include "Lives.h"

Lives::Lives()
    : m_lives(3)
    , m_texture(0)
    , m_font(nullptr)
    , lives_width(NULL)
    , lives_height(NULL)
{
    if (TTF_Init() == -1) {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
    }

    m_font = TTF_OpenFont("ShineTypewriter-lgwzd.ttf", 48);
    if (!m_font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    updateIMG("Lives: 3");      // put lives as 3 at the start of application
    updateTextureFromIMG("lives.png");      // renders png
}   

Lives::~Lives()
{
}

void Lives::decreaseLives(int amount)       // decreases lives 
{
	m_lives -= amount;
	std::string livesText = "Lives: " + std::to_string(m_lives);
	updateIMG(livesText);
	std::cout << livesText << std::endl;
	updateTextureFromIMG("Lives.png");
}

void Lives::draw(uiShader& uishader)        // creates quad for the lives 
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    if (!quadVAO)
    {
        std::cout << "Rebuilding quad" << std::endl;
        setupQuad();
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Lives::setupQuad()
{
    float w = static_cast<float>(lives_width);
    float h = static_cast<float>(lives_height);

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

void Lives::updateIMG(const std::string& newText)       // creates the lives texture into a png
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
    if (IMG_SavePNG(surface, "Lives.png") != 0) {
        std::cout << "Failed to save PNG: " << IMG_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);   
}

void Lives::updateTextureFromIMG(const std::string& imagePath)      // updates the texture on the application
{
    SDL_Surface* img = IMG_Load(imagePath.c_str());     // takes the image path
    if (!img)
    {
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    lives_width = img->w;
    lives_height = img->h;

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
