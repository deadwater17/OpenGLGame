#include "FragmentShader.h"
#include <iostream>

const GLchar* fragmentShaderSrc =
"void main()                       " \
"{                                 " \
" gl_FragColor = vec4(0, 0, 1, 1); " \
"}                                 ";


FragmentShader::FragmentShader() {
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderID, 1, &fragmentShaderSrc, NULL);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw std::runtime_error("Fragment shader compilation failed");
    }
}

FragmentShader::~FragmentShader() {
    glDeleteShader(shaderID);
}

GLuint FragmentShader::getID() const {
    return shaderID;
}