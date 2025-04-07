#include "Player.h"
#include "World.h"

Player::Player(World* _world)
    : m_world(_world)
    , m_pos(0,0,0)
    , Model("curuthers.obj")
{ }

void Player::update()
{
    if (m_world->keyboard.size() > SDLK_a && m_world->keyboard[SDLK_a])
    {
        m_pos.x++;
		std::cout << "Left" << std::endl;
    }
    if (m_world->keyboard.size() > SDLK_d && m_world->keyboard[SDLK_d])
    {
        m_pos.x--;
        std::cout << "Right" << std::endl;
    }
    if (m_world->keyboard.size() > SDLK_w && m_world->keyboard[SDLK_w])
    {
        m_pos.y++;
        std::cout << "Up" << std::endl;
    }
    if (m_world->keyboard.size() > SDLK_s && m_world->keyboard[SDLK_s])
    {
        m_pos.y--;
        std::cout << "Down" << std::endl;
    }
}

void Player::display()
{
    if (m_damaged)
    {
      //  m_world->pulse.draw(m_world.playermodel);
    }
    else
    {
        m_world->light.draw(m_world->playermodel,m_pos);
    }
}