#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>

class Shader
{
public:
	Shader();
	~Shader();

	void use() const { glUseProgram(programId); };
	GLuint getID() const { return programId; };

	void compile(const GLchar* vertexSrc, const GLchar* fragmentSrc);

private:
	GLuint programId;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};