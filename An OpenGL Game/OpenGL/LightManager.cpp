#include "LightManager.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <string>



LightManager::LightManager()
{
    lights.push_back({
    glm::vec3(0.0f, 5.0f, 0.0f), // Position above player
    glm::vec3(1.0f, 1.0f, 1.0f), // White light
    1.0f                         // Intensity
        });
}

void LightManager::update(const glm::vec3& playerPos)
{
    // Spawn new lights ahead of player
    while (playerPos.z + 50.0f > lastSpawnZ + spacing) {
        lastSpawnZ += spacing;
        lights.push_back(
            {
            glm::vec3(0.0f, 5.0f, lastSpawnZ),
            glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f
            });

        std::cout << "[LightManager] Spawned light at Z = " << lastSpawnZ << std::endl;

    }

    // Cull lights behind player
    lights.erase(
        std::remove_if(lights.begin(), lights.end(),
            [&](const Light& light) {
                return light.position.z < playerPos.z - cullDistanceBehind;
            }),
        lights.end()
    );
}

void LightManager::sendToShader(GLuint shaderProgram) 
{
    int count = std::min((int)lights.size(), maxLights);
    glUniform1i(glGetUniformLocation(shaderProgram, "u_NumLights"), count);

    for (int i = 0; i < count; ++i) {
        std::string base = "u_Lights[" + std::to_string(i) + "]";
        glUniform3fv(glGetUniformLocation(shaderProgram, (base + ".position").c_str()), 1, glm::value_ptr(lights[i].position));
        glUniform3fv(glGetUniformLocation(shaderProgram, (base + ".color").c_str()), 1, glm::value_ptr(lights[i].color));
        glUniform1f(glGetUniformLocation(shaderProgram, (base + ".intensity").c_str()), lights[i].intensity);
    }
}
