#pragma once  
#include <glm/gtc/matrix_transform.hpp>  
#include <SDL2/SDL.h>  
#include "Model.h"

struct World;  

struct Player : public Model
{  
	Player(World* _world);  
    void update();  
    void display();  

private:  
	bool m_damaged = false;
	World* m_world;  
	glm::vec3 m_pos;  
};
