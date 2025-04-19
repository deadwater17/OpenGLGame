#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "glm/glm.hpp"
#include "Player.h"
#include "Shader.h"

struct World;

struct Camera
{
	Camera(Player* player, Shader* shader);
	~Camera();

    void update(float dt = 0.0f);

    // Camera properties
    glm::vec3 position = glm::vec3(0.0f);
    float distanceFromPlayer = 5.0f;
    float heightFromPlayer = 3.0f;
    float fov = 75.0f;

    // Get view matrix for other calculations
    const glm::mat4& getViewMatrix() const { return viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
    

private:
    void updateProjection();
    void updateView();
    void sendToShader();

    Player* m_player = nullptr;
    Shader* m_shader = nullptr;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};