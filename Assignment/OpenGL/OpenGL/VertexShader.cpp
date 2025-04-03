#include <iostream>
#include "VertexShader.h"


const GLchar* vertexShaderSrc =
    "attribute vec3 in_Position;            " \
    "                                       " \
    "void main()                            " \
    "{                                      " \
    " gl_Position = vec4(in_Position, 1.0); " \
    "}                                      ";


VertexShader::VertexShader() {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderID, 1, &vertexShaderSrc, NULL);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw std::runtime_error("Vertex shader compilation failed");
    }
}

VertexShader::~VertexShader() {
    glDeleteShader(shaderID);
}

GLuint VertexShader::getID() const {
    return shaderID;
}