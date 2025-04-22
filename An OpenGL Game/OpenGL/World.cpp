#include "World.h"

const GLfloat positions[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

const GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
};

World::World()
	: shader(),
    mesh(std::make_unique<Mesh>(positions, sizeof(positions), colors, sizeof(colors)))
    //player(),
    //enemy(),
    //camera(&player)
{}

void World::update(float dt)
{
    handleInput(dt);
}

void World::handleInput(float dt)
{
    //player.update(dt);
    //enemy.update(dt);
    //camera.update();
}



void World::render()
{
    shader.use();


    // Temporary identity matrices (until camera integrate)
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);

    //glm::mat4 projection = camera.getProjectionMatrix();
    //glm::mat4 view = camera.getViewMatrix();

	// Projection
    GLint projLoc = glGetUniformLocation(shader.getID(), "u_Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Camera
    GLint viewLoc = glGetUniformLocation(shader.getID(), "u_View");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	mesh->draw(shader);
}
