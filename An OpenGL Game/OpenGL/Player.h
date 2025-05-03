#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"


#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>

class Player
{
public:
	Player(const std::string& modelPath, const std::string& texturePath);
	~Player();

	void handleInput(const Uint8* keybaordState, float dt);
	void update(float dt);
	void draw(Shader& shader);

	glm::vec3 getPosition() const { return m_position; }

	float getSpeed() const { return m_speed; }

	int playerHP;

private:
	Model m_model;
	Texture m_texture;
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	float m_speed = 10.0f;


	int currentLane = 0;
	int m_laneSpace = 20;
	int minLane = -1;
	int maxLane = 1;

};