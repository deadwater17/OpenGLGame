#include "Camera.h"

#include <iostream>

Camera::Camera()
	: m_position(0.0f, 0.0f, -3.0f)
	, m_target(0.0f)
	, m_tilt(0.0f, 3.0f, 0.0f)
	, m_distance(5.0f)
	, m_smoothSpeed(5.0f)
{}

Camera::~Camera()
{}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_target, m_tilt);
}

void Camera::update(const glm::vec3& target, float dt)
{
	m_target = target;

	glm::vec3 desiredPosition = target - glm::vec3(0.0f, -2.5f, m_distance); 

	// Smooth camera movement
	m_position = glm::mix(m_position, desiredPosition, m_smoothSpeed *dt);

	std::cout << "Camera: " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
}
