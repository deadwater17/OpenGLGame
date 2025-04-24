#include "Road.h"

static const GLfloat roadVertices[] = {
	// Positions
    -5.0f, 0.0f,  0.0f,
     5.0f, 0.0f,  0.0f,
    -5.0f, 0.0f, -10.0f,
     5.0f, 0.0f,  0.0f,
     5.0f, 0.0f, -10.0f,
    -5.0f, 0.0f, -10.0f,
};

static const GLfloat roadColors[] = {
    0.2f, 0.2f, 0.2f, 1.0f,
    0.2f, 0.2f, 0.2f, 1.0f,
    0.2f, 0.2f, 0.2f, 1.0f,
    0.2f, 0.2f, 0.2f, 1.0f,
    0.2f, 0.2f, 0.2f, 1.0f,
    0.2f, 0.2f, 0.2f, 1.0f,
};


Road::Road(const std::string& modelPath, const std::string& texturePath)
    : position(0.0f,-1.0f,0.0f)
{
    mesh = std::make_unique<Mesh>(modelPath);

	texture = std::make_unique<Texture>(texturePath);
}

Road::~Road()
{
}

void Road::update(float dt, float playerSpeed)
{
    position.z -= playerSpeed * dt;

	// Puts the road back to the start when it goes off screen
    if (position.z < -100.0f)
        position.z = 0.0f;
}

void Road::draw(Shader& shader)
{
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    GLint modelLoc = glGetUniformLocation(shader.getID(), "u_Model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
	texture->bind();
    mesh->draw(shader);
}

void Road::setPosition(const glm::vec3& pos)
{
    position = pos;
}

const glm::vec3& Road::getPosition() const
{
	return position;
}