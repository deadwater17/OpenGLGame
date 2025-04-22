#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "Model.h"
#include "World.h"

struct PlayerController : public Model
{

	PlayerController(World* _world);
	void update();
	void draw();
	void userInput(const std::vector <int>& keyboard, float dt);
	
	Model playermodel;
	
	World* m_world;

	glm::vec3 playerPos;
	float m_speed = 0.01f;
};