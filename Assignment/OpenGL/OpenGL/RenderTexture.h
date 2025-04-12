#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <vector>

struct RenderTexture
{
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void bind();
	void unbind();
	GLuint getTexture() { return m_texId; }


private:
	GLuint m_fboId;		// frame buffer
	GLuint m_texId;		// tex 
	GLuint m_rboId;		// render buffer
};

inline RenderTexture::RenderTexture(int _width, int _height)
{
	glGenFramebuffers(1, &m_fboId);
	if (!m_fboId)
	{
		throw std::exception();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);

	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

inline RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers;
	glDeleteTextures;
	glDeleteRenderbuffers;
}

void RenderTexture::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, getTexture());
}