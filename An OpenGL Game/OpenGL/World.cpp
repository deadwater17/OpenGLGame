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
	: shader()
    , mesh(std::make_unique<Mesh>(positions, sizeof(positions), colors, sizeof(colors)))
    , player("curuthers.obj","Whiskers_diffuse.png")
	, road("ground.obj","ground_Diffuse.png")
    , camera()
    //enemy()
{
    // spawns 10 roads ahead first
    for (int i = 0; i < 10; ++i) {
        road.setPosition(glm::vec3(0.0f, -10.0f, i * m_tileLength));
        m_roads.push_back(road);
    }


}

void World::update(float dt, const Uint8* keyboardState)
{
    handleInput(dt, keyboardState);
	player.update(dt);
    camera.update(player.getPosition(), dt);
    handleRoads();
	//road.update(dt, player.getSpeed());
    //enemy.update(dt);

}

void World::handleInput(float dt, const Uint8* keyboardState)
{   
	player.handleInput(keyboardState, dt);
}

void World::handleRoads()
{
	glm::vec3 playerPos = player.getPosition();

    for (auto& road : m_roads) {
        if (road.getPosition().z + m_tileLength < playerPos.z)
        {
            road.setPosition(road.getPosition() + glm::vec3(0.0f, -15.0f, m_tileLength * m_roads.size()));
        }
    }
}


void World::render()
{
    shader.use();

    // Projection
    //glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(120.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    GLint projLoc = glGetUniformLocation(shader.getID(), "u_Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    //glm::mat4 projection = camera.getProjectionMatrix();

    // Camera
    glm::mat4 viewMatrix = camera.getViewMatrix();
    GLint viewLoc = glGetUniformLocation(shader.getID(), "u_View");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    mesh->draw(shader);
	//std::cout << "Mesh Drawn" << std::endl;

	player.draw(shader);
	//std::cout << "Player Drawn" << std::endl;

    for(auto& road : m_roads)
	{
		road.draw(shader);
	}
	//std::cout << "Road Drawn" << std::endl;
}
