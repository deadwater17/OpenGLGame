#pragma once
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	GLuint VertexShader();
	GLuint FragmentShader();

private:
	GLuint programId;
};
