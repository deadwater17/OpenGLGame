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

	void bind() const;
	GLuint getID();

private:
	std::vector<unsigned char> m_data;
	mutable GLuint m_id;
	int m_width;
	int m_height;
	mutable bool m_dirty;
};

