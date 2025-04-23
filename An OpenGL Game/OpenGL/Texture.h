#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <vector>
#include <exception>

struct Texture
{
	Texture(const std::string& _path);
	~Texture();

	GLuint id();

private:
	std::vector<unsigned char> m_data;
	GLuint m_id;
	int m_width;
	int m_height;
	bool m_dirty;
};

