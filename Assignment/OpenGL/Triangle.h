/*
#pragma once
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

struct Triangle
{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3 normal;
};

void collision_triangles(std::vector<Triangle>& _triangles)
{

}

glm::vec3 generate_normal(const glm::vec3& _a, const glm::vec3& _b, const glm::vec3& _c)
{
	glm::vec3 ab = _b - _a;
	glm::vec3 ac = _c - _a;

	glm::vec3 rtn = glm::cross(ab, ac);

	return glm::normalize(rtn);
}

bool tribox_colliding(const glm::vec3& _a, const glm::vec3& _as, const std::vector<Triangle>& _triangles)
{

}
*/