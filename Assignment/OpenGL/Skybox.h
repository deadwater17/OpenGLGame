#pragma once
#include <GL/glew.h>
#include "Shader.h"

struct Skybox
{
	Skybox(const std::string& _path);
	~Skybox();

	unsigned int loadSkybox(const std::vector<std::string>& faces);

	float skyboxVertices[24] = {
		-1,-1,1,
		1,-1,1,
		1,-1,-1,
		-1,-1,-1,
		-1,1,1,
		1,1,1,
		1,1,1,
		-1,1,-1
	};

	unsigned int skybox[36] =
	{
		1,2,6,
		6,5,1,

		0,4,7,
		7,3,0,

		4,5,6,
		6,7,4,

		0,3,2,
		2,1,0,

		0,1,5,
		5,4,0,

		3,7,6,
		6,2,3,
	};

    unsigned int cubemapTexture = loadSkybox(faces);
};