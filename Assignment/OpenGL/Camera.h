#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "glm/glm.hpp"
#include "Player.h"
#include "Shader.h"

struct World;

struct Camera
{
	Camera(Player* player, World* world, Shader* shader);
	~Camera();
	void update();
	void getPlayerPos();

	const glm::vec3 getCameraPosition()	const { return CameraPos; }
	Player player;

	void camInit(const glm::vec3& position, const Camera& camera);

private:
	glm::vec3 CameraPos;
	Player* m_player;
	Shader* m_shader;

};