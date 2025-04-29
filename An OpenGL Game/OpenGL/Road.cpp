#include "Road.h"

Road::Road(const std::string& modelPath, const std::string& texturePath)
    : position(0.0f,-2.8f,0.0f)
	, scale(0.01f, 1.0f, 0.01f)
    , model(modelPath)
	, texture(texturePath)
{
    
}

Road::~Road()
{}

void Road::update(float dt, float playerSpeed)
{
    // unneeded now, moved to world.cpp    
}

void Road::draw(Shader& shader)
{
    shader.use();   // might not be neeeded

    // Build the model matrix
    glm::mat4 modelMat = glm::mat4(1.0f);

    // translate into world
    modelMat = glm::translate(modelMat, position);

    // Scales the road
    modelMat = glm::scale(modelMat, scale);

    GLint modelLoc = glGetUniformLocation(shader.getID(), "u_Model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getID());

    // Draw model
    glBindVertexArray(model.vao_id());
    glDrawArrays(GL_TRIANGLES, 0, model.vertex_count());
    glBindVertexArray(0);

	//std::cout << "Road: " << position.x << " " << position.y << " " << position.z << std::endl;
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