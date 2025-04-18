#include "Camera.h"

Camera::Camera(Player* player, World* world)
    : player(world), 
    m_player(player),
    CameraPos(0,0,0)
{

}

Camera::~Camera()
{}

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


