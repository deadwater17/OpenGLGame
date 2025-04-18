#include "BoxCollider.h"

bool aabb_collision(const glm::vec3& _a, const glm::vec3& _as, const glm::vec3& _b, const glm::vec3& _bs)
{
    glm::vec3 ahs = _as / 2.0f;
    glm::vec3 bhs = _bs / 2.0f;

    if (_a.x > _b.x) //checks if collision on the x axis has happened
    {
        if (_b.x + bhs.x < _a.x - ahs.x)
        {
            return false;
        }
    }
    else
    {
        if (_a.x + ahs.x < _b.x - bhs.x)
        {
            return false;
        }
    }
    if (_a.y > _b.y) //checks if collision on the y axis has happened
    {
        if (_b.y + bhs.y < _a.y - ahs.y)
        {
            return false;
        }
    }
    else
    {
        if (_a.y + ahs.y < _b.y - bhs.y)
        {
            return false;
        }
    }
    if (_a.z > _b.z) //checks if collision on the z axis has happened
    {
        if (_b.z + bhs.z < _a.z - ahs.z)
        {
            return false;
        }
    }
    else
    {
        if (_a.z + ahs.z < _b.z - bhs.z)
        {
            return false;
        }
    }
}

glm::vec3 aabb_response(glm::vec3& _a, const glm::vec3& _as, const glm::vec3& _b, const glm::vec3& _bs)
{
    float amount = 0.1f;
    float step = 0.1f;

    while (true)
    {
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.x += amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.x -= amount;
        _a.x -= amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.x += amount;
        _a.z += amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.z -= amount;
        _a.z -= amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.z += amount;
        _a.y += amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.y -= amount;
        _a.y -= amount;
        if (!aabb_collision(_a, _as, _b, _bs)) break;
        _a.y += amount;

        amount += step;
    }
    return _a;
}