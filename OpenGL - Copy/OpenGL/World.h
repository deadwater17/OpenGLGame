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
	
	std::vector<Enemy> enemies;

	World(const GLchar* VertexSrc, const GLchar* FragmentSrc);
	void render();
	void handleInput(float dt);
};