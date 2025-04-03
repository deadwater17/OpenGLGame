#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &VAO);
}

void VertexArray::bind() const
{
    glBindVertexArray(VAO);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
