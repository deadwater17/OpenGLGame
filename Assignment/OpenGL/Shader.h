#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	GLuint compileShader(const char* src, GLenum type);
	
	GLuint getID() const { return programId; };

	void draw(const Model& model, const glm::vec3& position, const Camera& camera);

private:
	GLuint programId;
	GLuint vertexShaderId;
	GLuint fragmentShaderId;
};
