#include "Camera.h"

#include <iostream>

Camera::Camera()
	: m_position(0.0f, 3.0f, -3.0f)
	, m_target(0.0f)
	, m_tilt(0.0f, 3.0f, 0.0f)
	, m_distance(5.0f)
	, m_smoothSpeed(5.0f)
{}

Camera::~Camera()
{}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_target, m_tilt);		// set behind player model and tilts camera
}

void Camera::update(const glm::vec3& target, float dt)
{
	m_target = target;

	glm::vec3 desiredPosition = target - glm::vec3(0.0f, -5.0f, m_distance); 

	// Camera pos
	m_position = desiredPosition;
}
