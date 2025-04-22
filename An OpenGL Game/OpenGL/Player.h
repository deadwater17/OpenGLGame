#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Player
{
public:
	Player(const std::string& modelPath, const std::string& texturePath);
	~Player();

	void handleInput(const Uint8* keybaordState, float dt);
	void update(float dt);
	void draw(Shader& shader);

	const glm::vec3 getPosition() const { return m_position; }

private:
	Model m_model;
	Texture m_texture;
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	float m_speed = 1.0f;
};