#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh(const GLfloat* positiondata, size_t pSize, const GLfloat* colorsData, size_t cSize)
{
	GLuint positionsVboID = createVBO(positiondata, pSize);
    GLuint colorsVboId = createVBO(colorsData, cSize);
    GLuint VAO = createVAO(positionsVboID, colorsVboId);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &positionsVboID);
    glDeleteBuffers(1, &colorsVboId);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw(Shader& shader) const
{
    shader.use();                    // Activate the shader (assuming Shader has a use() method)
    glBindVertexArray(VAO);         // Bind the VAO for this mesh

    glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw 3 vertices as a triangle

    glBindVertexArray(0);
}

GLuint Mesh::createVBO(const GLfloat* data, size_t dataSize)
{
    GLuint vboID = 0;
    glGenBuffers(1, &vboID);
    if (!vboID) {
        throw std::runtime_error("Failed to initialize VBO on GPU");
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vboID;
}

GLuint Mesh::createVAO(GLuint positionsVboID, GLuint colorsVboId)
{
    GLuint vaoId = 0;
    glGenVertexArrays(1, &vaoId);
    if (!vaoId) {
        throw std::runtime_error("Failed to initialize VAO on GPU");
    }
    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, positionsVboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vaoId;
}


