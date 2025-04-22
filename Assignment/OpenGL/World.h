#pragma once
#include "Shader.h"
#include "Model.h"
#include "Player.h"
#include "Camera.h"

struct Enemy;

struct World
{
	Shader shader;
	Player player;
	Camera camera;

	std::vector<int> keyboard;

	Model playermodel;
	Model plane;
	Model enemyModel;

	glm::vec3 enemyPos;


	
	World(const GLchar* VertexSrc, const GLchar* FragmentSrc);
	void render();
	void handleInput(float dt);

	void drawing();

};