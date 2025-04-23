#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"
#include "Player.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class World
{
public:
	World();
	void update(float dt, const Uint8* keyboardState); 
	void handleInput(float dt, const Uint8* keyboardState);
	void render();

private:
	Shader shader;
	std::unique_ptr<Mesh> mesh;
	Player player;

	// Need to be implemented
	//Enemy enemy;
	//Camera camera;
};