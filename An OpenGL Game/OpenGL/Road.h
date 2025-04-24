#pragma once
#include "Mesh.h"
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
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getPosition() const;

private:
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Texture> texture;
	glm::vec3 position;
};