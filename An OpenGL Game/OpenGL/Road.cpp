#include "Road.h"

Road::Road(const std::string& modelPath, const std::string& texturePath)
    : position(0.0f,-10.0f,0.0f)
	, position2(0.0f, 10.0f, 0.0f)
	, scale(1.0f, 1.0f, 1.0f)
    , model(modelPath)
	, texture(texturePath)
{
    
}

Road::~Road()
{}

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
    shader.use();

    // Build the model matrix:
    glm::mat4 modelMat = glm::mat4(1.0f);

    // 1) Translate into world:
    modelMat = glm::translate(modelMat, position);

    // 2) Rotate 90‹ around X (so it lies flat):
    modelMat = glm::rotate(
        modelMat,
        glm::radians(90.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    );

    // 3) Scale if you need:
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

	std::cout << "Road: " << position.x << " " << position.y << " " << position.z << std::endl;
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