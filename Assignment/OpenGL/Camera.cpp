#include "Camera.h"

Camera::Camera(Player* player, Shader* shader)
    : m_player(player),
    m_shader(shader)
{
    // Initialize matrices
    updateProjection();
}

Camera::~Camera()
{}

void Camera::update(float dt)
{
    if (!m_player || !m_shader) return;

    updateView();
    sendToShader();
}

void Camera::updateView()
{
    if (!m_player) return;

    // Calculate camera position behind and above player
    position = m_player->playerPos;
    position.z += distanceFromPlayer; // Move back
    position.y += heightFromPlayer;   // Move up

    // Create view matrix looking at player
    viewMatrix = glm::lookAt(
        position,                   // Camera position
        m_player->playerPos,        // Look at player
        glm::vec3(0.0f, 1.0f, 0.0f) // Up vector
    );
}

void Camera::updateProjection()
{
    // Standard perspective projection
    projectionMatrix = glm::perspective(
        glm::radians(fov),          // Field of view
        800.0f / 600.0f,            // Aspect ratio (update if window resizes)
        0.1f,                       // Near plane
        100.0f                      // Far plane
    );
}

void Camera::sendToShader()
{
    if (!m_shader) return;

    // Projection
    GLint projLoc = glGetUniformLocation(m_shader->getID(), "u_Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Camera
    GLint viewLoc = glGetUniformLocation(m_shader->getID(), "u_View");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Camera Pos
    GLint viewPosLoc = glGetUniformLocation(m_shader->getID(), "u_ViewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(position));
}