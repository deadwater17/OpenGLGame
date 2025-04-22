#include "Player.h"
#include "World.h"

Player::Player(World* _world)
    : m_world(_world)
    , playerPos(0, 0, -3)
    , Model("curuthers.obj")
{}

void Player::update()
{ 
    display();
}

void Player::display()
{
    //m_world->basic.draw(m_world->playermodel,playerPos, m_world->camera);
    std::cout << "Position: (" << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << ")" << std::endl;
}

void Player::userInput(const std::vector <int>& keyboard, float dt)
{
    if (keyboard[SDL_SCANCODE_W]) 
    {
        playerPos.z -= m_speed*dt; // Move forward
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