#pragma once
#include "Texture.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>

class Barrier
{
public:
	Barrier(const std::string& modelPath, const std::string& texturePath);
	~Barrier();

	void update(float dt, float playerSpeed);
	void draw(Shader& shader);
	void setScale(const glm::vec3& scl);
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getPosition() const;

	bool getHasCollided() const { return hasCollidedWithPlayer; }
	void setHasCollided(bool collided) { hasCollidedWithPlayer = collided; }
private:
	Model m_model;
	Texture m_texture;
	glm::vec3 scale;
	glm::vec3 m_position;

	bool hasCollidedWithPlayer = false;


};