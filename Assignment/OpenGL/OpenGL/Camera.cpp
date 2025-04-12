#include "Camera.h"

Camera::Camera()
{
	cameraPos = glm::perspective(glm::radians(120.0f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
}

Camera::~Camera()
{
}

