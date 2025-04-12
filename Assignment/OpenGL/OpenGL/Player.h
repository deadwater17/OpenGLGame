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
	void userInput(const std::vector <int>& keyboard);

	World* m_world; 	
	
	glm::vec3 m_pos;  
	glm::vec3 playerPos;
private:  
	bool m_damaged = false;
	float m_speed = 1.0f;
};
