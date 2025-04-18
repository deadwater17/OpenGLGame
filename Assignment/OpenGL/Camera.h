#pragma once
#include "Player.h"
#include "glm/glm.hpp"

struct World;

struct Camera
{
	Camera() = delete;
	Camera(Player* player, World* world);
	~Camera();
	void update();
	void getPlayerPos();

	const glm::vec3 getCameraPosition()	const { return CameraPos; }
	Player player;

private:
	glm::vec3 CameraPos;
	Player* m_player;
};

