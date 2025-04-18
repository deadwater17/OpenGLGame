#pragma once
#include <glm/gtc/matrix_transform.hpp>

struct BoxCollider
{
public:
	bool aabb_collision(const glm::vec3& _a, const glm::vec3& _as, const glm::vec3& _b, const glm::vec3& _bs);
	glm::vec3 aabb_response(glm::vec3& _a, const glm::vec3& _as, const glm::vec3& _b, const glm::vec3& _bs);

	glm::vec3 size;
	glm::vec3 offset;

private:
	void onTick();
	void setSize(glm::vec3 size);
	void setOffset(glm::vec3 offset);
};
