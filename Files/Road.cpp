#include "Road.h"

Road::Road(const std::string& modelPath, const std::string& texturePath)
    : position(0.0f,-1.0f,0.0f)
	, scale(1.0f, 1.0f, 1.0f)
{
	model = std::make_unique<Model>(modelPath);

	texture = std::make_unique<Texture>(texturePath);
}

Road::~Road()
{
}

void Road::update(float dt, float playerSpeed)
{
    position.z -= playerSpeed * dt;
    position2.z -= playerSpeed * dt;

    // Reset if either has moved past the camera
    if (position.z < -100.0f)
        position.z = position2.z + 100.0f;

    if (position2.z < -100.0f)
        position2.z = position.z + 100.0f;
}

void Road::draw(Shader& shader)
{
    GLint modelLoc = glGetUniformLocation(shader.getID(), "u_Model");

    // First
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, scale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    texture->bind();
    model->draw(shader);

    // Second
    modelMatrix = glm::translate(glm::mat4(1.0f), position2);
    modelMatrix = glm::scale(modelMatrix, scale);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    model->draw(shader);
}

void Road::setScale(const glm::vec3& scl)
{
    scale = scl;
}

void Road::setPosition(const glm::vec3& pos)
{
    position = pos;
}

const glm::vec3& Road::getPosition() const
{
	return position;
}