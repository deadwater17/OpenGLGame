#include "Player.h"

Player::Player(const std::string& modelPath, const std::string& texturePath)
	: m_model(modelPath)
	, m_texture(texturePath)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_velocity(0.0f)
{

}

Player::~Player()
{}

void Player::update(float dt)
{
    m_position += m_velocity * dt;
}

void Player::handleInput(const Uint8* keyboardState, float dt)
{
    m_velocity = glm::vec3(0.0f);
    if (keyboardState[SDL_SCANCODE_W])
    {
        m_velocity.z -= 1.0f;
    }
    if (keyboardState[SDL_SCANCODE_S]) 
    {
        m_velocity.z += 1.0f;
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        m_velocity.x -= 1.0f;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        m_velocity.x += 1.0f;
    }

    if (glm::length(m_velocity) > 0.0f)
    {
        m_velocity = glm::normalize(m_velocity) * m_speed;
    }

	std::cout << "Player: " <<m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
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
