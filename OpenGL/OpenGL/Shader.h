#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	GLuint compileShader(const char* src, GLenum type);
	
	GLuint getID() const { return programId; };

private:
	GLuint programId;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};
