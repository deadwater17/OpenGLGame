#pragma once
#include <GL/glew.h>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    GLuint getID() const {
        return VAO;
    };

private:
    GLuint VAO;
};
