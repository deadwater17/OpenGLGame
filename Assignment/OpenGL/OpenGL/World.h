#pragma once
#include "Shader.h"
#include "Model.h"
#include "Player.h"

struct Enemy;

struct World
{
	Shader basic;
	std::vector<int> keyboard;

	Model playermodel;

	Player player;
	//std::vector<Enemy> enemies;

	glm::vec3 worldPos;

	World(const GLchar* VertexSrc, const GLchar* FragmentSrc);
	void render();

	void update();
};