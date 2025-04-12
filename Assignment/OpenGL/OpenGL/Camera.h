#pragma once
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Camera
{
public:
	Camera();
	~Camera();

	void CamUpdatePos();

	void CameraInput();

	glm::mat4 cameraPos;
private:
	const float cameraSpeed = 0.05f;
	const Uint8* state = SDL_GetKeyboardState(NULL);
};