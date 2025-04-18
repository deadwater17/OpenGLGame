#pragma once
#include "Player.h"

struct World;

struct Camera
{
	Camera(Player* player, World* world);
	~Camera();
	void update();
	void getPlayerPos();

	Player player;

private:
	glm::vec3 CameraPos;
	Player* m_player;
};
