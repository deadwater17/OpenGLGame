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
#include "Barrier.h"
#include "Render_Text_Texture.h"
#include "Load_Text_Texture.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class World
{
public:
	World(SDL_Window* window, SDL_Renderer* renderer);
	void update(float dt, const Uint8* keyboardState); 

	void render();

private:
	void handleInput(float dt, const Uint8* keyboardState);
	void updateRoads();
	void updateBarrier(float dt);

	Shader shader;

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::unique_ptr<Mesh> mesh;
	Player player;
	Camera camera;
	Road road;
	Barrier barrier;

	TTF_Font* font;
	
	int score;

	std::vector<Road> m_roads;
	const float m_tileLength = 78.5f;

	std::vector<Barrier> m_barriers;
	int m_laneSpace = 20;	
	float m_spawnTimer = 0.0f;
	float m_spawnInterval = 5.0f;

	// Need to be implemented
	//Enemy enemy;

};