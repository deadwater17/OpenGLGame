#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"

class World
{
public:
	World();
	void handleInput(float dt);
	void update(float dt);	
	void render();

private:
	Shader shader;
	std::unique_ptr<Mesh> mesh;

	// Need to be implemented
	//Player player;
	//Enemy enemy;
	//Camera camera;
};