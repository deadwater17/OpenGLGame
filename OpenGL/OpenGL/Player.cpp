#include "Player.h"
#include "World.h"

Player::Player(World* _world)
    : m_world(_world)
    , playerPos(0, 0, -3)
    , Model("curuthers.obj")
{ }

void Player::update()
{ 
    display();
}

void Player::display()
{
    m_world->basic.draw(m_world->playermodel,playerPos);
    //std::cout << "draws model" << std::endl;
}

void Player::userInput(const std::vector <int>& keyboard, float dt)
{
    if (keyboard[SDL_SCANCODE_W]) 
    {
        playerPos.z -= m_speed; // Move forward
		//std::cout << "moving" << std::endl;
        std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_S]) 
    {
        playerPos.z += m_speed; // Move backward
        //std::cout << "moving" << std::endl;
        std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_A]) 
    {
        playerPos.x -= m_speed; // Move left
        //std::cout << "moving" << std::endl;
        std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_D]) 
    {
        playerPos.x += m_speed; // Move right
        //std::cout << "moving" << std::endl;
        std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
    }
}