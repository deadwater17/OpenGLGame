#include "Barrier.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Barrier::Barrier(const std::string& modelPath, const std::string& texturePath)
    : m_model(modelPath)
    , m_texture(texturePath)
    , m_position(0.0f, -2.8f, 0.0f)
    , scale(15,15,15)
{
}

Barrier::~Barrier()
{}

void Barrier::update(float dt, float playerSpeed)
{
    m_position.z -= playerSpeed * dt;
}

void Barrier::draw(Shader& shader)
{
    shader.use();

    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_position);

    modelMat = glm::scale(modelMat, scale);

    GLint modelLoc = glGetUniformLocation(shader.getID(), "u_Model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.getID());

    glBindVertexArray(m_model.vao_id());
    glDrawArrays(GL_TRIANGLES, 0, m_model.vertex_count());
    glBindVertexArray(0);
}

void Barrier::setScale(const glm::vec3& scl)
{
    scale = scl;
}

void Barrier::setPosition(const glm::vec3& pos)
{
	m_position = pos;
}

const glm::vec3& Barrier::getPosition() const
{
	return m_position;
}
