#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

Texture::Texture(const std::string& _path)
	: m_id(0)
	, m_width(0)
	, m_height(0)
	, m_dirty(false)
{
	unsigned char* data = stbi_load(_path.c_str(), &m_width, &m_height, NULL, 4);

	if (!data)
	{
		throw std::exception();
	}

	for (size_t i = 0; i < m_width * m_height * 4; ++i)
	{
		m_data.push_back(data[i]);
	}

	stbi_image_free(data);
	m_dirty = true;
}

Texture::~Texture()
{
	if (m_id)
	{
		glDeleteTextures(1, &m_id);
	}
}

GLuint Texture::getID()
{
	bind();
	return m_id;
}

 void Texture::bind() const
{
	if (!m_id)
	{
		glGenTextures(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}
	}

	if (m_dirty)
	{
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, &m_data.at(0));

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		m_dirty = false;
	}
}
