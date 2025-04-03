#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <GL/glew.h>

class VertexShader {
public:
    VertexShader();
    ~VertexShader();
    GLuint getID() const;

private:
    GLuint shaderID;
};

#endif // VERTEX_SHADER_H