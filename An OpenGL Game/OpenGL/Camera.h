#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 getViewMatrix() const;

	void update(const glm::vec3& target, float dt);

private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_tilt;
	float m_distance;
	float m_smoothSpeed;
};
