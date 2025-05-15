#include "Player.h"

Player::Player(const std::string& modelPath, const std::string& texturePath)
	: m_model(modelPath)
	, m_texture(texturePath)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_velocity(0.0f)
    , scale (10,10,10)
{
    playerHP = 3;
}

Player::~Player()
{}

void Player::update(float dt)
{
    m_position += m_velocity * dt;
}

void Player::handleInput(const Uint8* keyboardState, float dt)
{
    m_velocity.z += 1.0f;

    //std::cout << "Player is at " << m_position.z << std::endl;

    static bool aPressed = false;
    static bool dPressed = false;

    if (keyboardState[SDL_SCANCODE_A]) {
        if (!aPressed && currentLane > minLane) {
            currentLane--;
            m_position.x = -currentLane * m_laneSpace;
        }
        aPressed = true;
    }
    else {
        aPressed = false;
    }

    if (keyboardState[SDL_SCANCODE_D]) {
        if (!dPressed && currentLane < maxLane) {
            currentLane++;
            m_position.x = -currentLane * m_laneSpace;
        }
        dPressed = true;
    }
    else {
        dPressed = false;
    }

    if (glm::length(m_velocity) > 0.0f)
    {
        m_velocity = glm::normalize(m_velocity) * m_speed;
    }

	//std::cout << "Player: " <<m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
}

void Player::draw(Shader& shader)
{
    shader.use();

    // Set model matrix uniform
    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_position);
    GLint modelLoc = glGetUniformLocation(shader.getID(), "u_Model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.getID());

    // Draw model
    glBindVertexArray(m_model.vao_id());
    glDrawArrays(GL_TRIANGLES, 0, m_model.vertex_count());
    glBindVertexArray(0);

	//std::cout << "Player is drawn" << std::endl;
}

void Player::setScale(const glm::vec3& scl)
{
    scale = scl;
}