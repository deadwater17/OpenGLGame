#include "Player.h"
#include "World.h"

Player::Player(World* _world)
    : m_world(_world)
    , m_pos()
    , playerPos (0.0f,0.0f,-5.0f)

{
    m_pos = m_world->playermodel.getPosition(); // Set m_pos to playermodel's position

}

void Player::update()
{ 
	userInput(m_world->keyboard);
}

void Player::display()
{
    if (m_damaged)
    {
      //  m_world->pulse.draw(m_world.playermodel);
    }
    else
    {
        //m_world->light.draw(m_world->playermodel,m_pos);
    }
}

void Player::userInput(const std::vector <int>& keyboard)
{
    if (keyboard[SDL_SCANCODE_A]) 
    {
        playerPos.x -= playerPos.x - m_speed; // Move left
        std::cout << "moving left" << std::endl;
    }
    if (keyboard[SDL_SCANCODE_D]) 
    {
        playerPos.x += playerPos.x - m_speed; // Move right
        std::cout << "moving right" << std::endl;
    }
}