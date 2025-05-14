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
	return glm::lookAt(m_position, m_target, m_tilt); //glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); 
}

void Camera::update(const glm::vec3& target, float dt)
{
	m_target = target;

	glm::vec3 desiredPosition = target - glm::vec3(0.0f, -5.0f, m_distance); 

	// Camera pos
	m_position = desiredPosition;
	// Smooth camera movement
	//m_position = glm::mix(m_position, desiredPosition, m_smoothSpeed *dt);

	//std::cout << "Camera: " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
}
