#include "Player.h"
#include "World.h"

Player::Player(World* _world)
    : m_world(_world)
    , m_pos(0, 0, -2.0f)
    , playerPos (0.0f,0.0f,-2.0f)
    , Model("curuthers.obj")
{ }

void Player::update()
{ }

void Player::display()
{
    if (m_damaged)
    {
      //  m_world->pulse.draw(m_world.playermodel);
    }
    else
    {
        m_world->light.draw(m_world->playermodel,playerPos);
		std::cout << "light.draw" << std::endl;
    }
}

void Player::userInput(const std::vector <int>& keyboard)
{
    if (keyboard[SDL_SCANCODE_W]) 
    {
        playerPos.z -= m_speed; // Move forward
		//std::cout << "moving" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_S]) 
    {
        playerPos.z += m_speed; // Move backward
        //std::cout << "moving" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_A]) 
    {
        playerPos.x -= m_speed; // Move left
        //std::cout << "moving" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_D]) 
    {
        playerPos.x += m_speed; // Move right
        //std::cout << "moving" << std::endl;
    }
}