#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(const VertexShader& vertexShader, const FragmentShader& fragmentShader) {
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());
    glBindAttribLocation(programID, 0, "in_Position");
    glLinkProgram(programID);

    GLint success;

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        throw std::runtime_error("Shader program linking failed");
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

GLuint ShaderProgram::getID() const {
    return programID;
}
