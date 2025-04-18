#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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