#include "PlayerC.h"

PlayerController::PlayerController(World* _world)
    : m_world(_world)
    , playermodel("curuthers.obj")
{
    playerPos = glm::vec3(0, 0, -3);
}


void PlayerController::update()
{
    m_world->shader.draw(playermodel, playerPos);
}

void PlayerController::userInput(const std::vector<int>& keyboard, float dt)
{
    if (keyboard[SDL_SCANCODE_W])
    {
        playerPos.z -= m_speed * dt; // Move forward
        //std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_S])
    {
        playerPos.z += m_speed * dt; // Move backward
        //std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_A])
    {
        playerPos.x -= m_speed * dt; // Move left
        //std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_D])
    {
        playerPos.x += m_speed * dt; // Move right
        //std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
}

void PlayerController::draw()
{
	
}