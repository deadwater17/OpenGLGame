#pragma once
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

class Road
{
public:
	Road(const std::string& modelPath, const std::string& texturePath);
	~Road();

	void update(float dt, float playerSpeed);

	void draw(Shader& shader);
	void setScale(const glm::vec3& scl);
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getPosition() const;

private:
	std::unique_ptr<Model> model;
	std::unique_ptr<Texture> texture;
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 position2;
};