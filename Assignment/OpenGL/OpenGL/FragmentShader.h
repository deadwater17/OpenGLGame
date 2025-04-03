#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include <GL/glew.h>

class FragmentShader {
public:
    FragmentShader();
    ~FragmentShader();
    GLuint getID() const;

private:
    GLuint shaderID;
};

#endif // FRAGMENT_SHADER_H