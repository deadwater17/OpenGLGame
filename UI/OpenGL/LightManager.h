#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>


struct Light {
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};

class LightManager 
{
public:
    LightManager();

    void update(const glm::vec3& playerPos);
    void sendToShader(GLuint shaderProgram);

private:
    std::vector<Light> lights;
    float lastSpawnZ = 0.0f;
    const float spacing = 20.0f;
    const float cullDistanceBehind = 10.0f;
    const int maxLights = 8;
};
