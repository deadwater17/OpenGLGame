#include "Camera.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Camera::Camera(Player* player, World* world, Shader* shader)
    : player(world), 
    m_player(player),
    CameraPos(0,0,0),
	m_shader(shader)
{

}

Camera::~Camera()   {}

void Camera::update()
{
    getPlayerPos();
}

void Camera::getPlayerPos()
{
    if (m_player)
    {
        // Update the camera position to follow the player's position
        CameraPos = m_player->playerPos + glm::vec3(0.0f, 0.0f, 3.0f);
    }
    std::cout << "Camera x: " << CameraPos.x << " ,camera z: " << CameraPos.z<< std::endl;
}

void Camera::camInit(const glm::vec3& position, const Camera& camera)
{
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(120.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Set up the camera matrix
    glm::vec3 camPos = camera.getCameraPosition();
    glm::mat4 viewMatrix = glm::lookAt(
        camPos,                     // Camera position
        camPos + glm::vec3(0, 0, 0), // Looking down -Z axis (adjust as needed)
        glm::vec3(0, 0, 0)          // Up vector
	);

    // Projection
    GLint projLoc = glGetUniformLocation(m_shader->getID(), "u_Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Camera
    GLint viewLoc = glGetUniformLocation(m_shader->getID(), "u_View");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Camera Pos
    GLint viewPosLoc = glGetUniformLocation(m_shader->getID(), "u_ViewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(camPos));
}


