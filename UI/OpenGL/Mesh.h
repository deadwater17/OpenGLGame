#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

class Shader;

class Mesh 
{
public:
	Mesh(const GLfloat* positiondata, size_t pSize, const GLfloat* colorsData, size_t cSize);
	~Mesh();
	void draw(Shader& shader) const;

private:
	GLuint VAO, positionsVboID, colorsVboId;

	GLuint createVBO(const GLfloat* data, size_t dataSize);
	GLuint createVAO(GLuint positionsVboID, GLuint colorsVboId);
};