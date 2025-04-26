#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Camera.h"
#include "Road.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class World
{
public:
	World();
	void update(float dt, const Uint8* keyboardState); 

	void render();

private:
	void handleInput(float dt, const Uint8* keyboardState);
	void handleRoads();


	Shader shader;
	std::unique_ptr<Mesh> mesh;
	Player player;
	Camera camera;
	Road road;
	

	std::vector<Road> m_roads;
	const float m_tileLength = 50.0f;
	// Need to be implemented
	//Enemy enemy;

};