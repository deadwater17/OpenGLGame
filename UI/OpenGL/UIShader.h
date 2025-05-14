#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>

class uiShader
{
public:
	uiShader();
	~uiShader();

	void use() const { glUseProgram(programId); };
	GLuint getID() const { return programId; };

	void compile(const GLchar* uivertexSrc, const GLchar* uifragmentSrc);

private:
	GLuint programId;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
}; 
