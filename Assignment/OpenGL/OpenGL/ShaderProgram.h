#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "VertexShader.h"
#include "FragmentShader.h"

class ShaderProgram {
public:
    ShaderProgram(const VertexShader& vertexShader, const FragmentShader& fragmentShader);
    ~ShaderProgram();
    void use() const;
    GLuint getID() const;

private:
    GLuint programID;
};

#endif // SHADER_PROGRAM_H