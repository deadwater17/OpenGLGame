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
    , player("models/curuthers.obj","Whiskers_diffuse.png")
	, road("ground.obj","ground_Diffuse.png")
	, barrier("barrier.obj", "barrier_Diffuse.png")
    , camera()
{
	glm::vec3 roadPos = road.getPosition();
    // spawns 10 roads ahead first
    for (int i = 0; i < 10; ++i) {
        road.setPosition(glm::vec3(0.0f, roadPos.y, i * m_tileLength));
        m_roads.push_back(road);
    }


}

void World::update(float dt, const Uint8* keyboardState)
{
    handleInput(dt, keyboardState);
	player.update(dt);
    camera.update(player.getPosition(), dt);

    updateRoads();
    updateBarrier(dt);
	//road.update(dt, player.getSpeed());
    //enemy.update(dt);

}

void World::handleInput(float dt, const Uint8* keyboardState)
{   
	player.handleInput(keyboardState, dt);
}

void World::updateRoads()
{
	glm::vec3 playerPos = player.getPosition();
	glm::vec3 roadPos = road.getPosition();

    for (auto& road : m_roads) 
    {
        if (road.getPosition().z + m_tileLength < playerPos.z)
        {
            road.setPosition(road.getPosition() + glm::vec3(0.0f, roadPos.y, m_tileLength * m_roads.size()));
        }
    }
}

void World::updateBarrier(float dt)
{
	glm::vec3 barrierPos = barrier.getPosition();

    std::cout << "Updating barriers..." << std::endl;
    std::cout << "Current barrier count: " << m_barriers.size() << std::endl;

    // Iterate through barriers and update them
    for (size_t i = 0; i < m_barriers.size(); ++i) {
        try {
            // Access barrier using at() to catch out_of_range
            Barrier& b = m_barriers.at(i);
            std::cout << "Updating barrier " << i << " at position " << b.getPosition().z << std::endl;
            b.update(dt, player.getSpeed());
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught out_of_range exception while accessing barrier " << i << std::endl;
        }
    }

    // Spawn new barriers every few seconds
    m_spawnTimer += dt;
    if (m_spawnTimer >= m_spawnInterval)
    {
        m_spawnTimer = 0.0f;

        // Randomly choose a lane: -1 (left), 0 (middle), 1 (right)
        int lane = (rand() % 3) - 1;
        float laneOffset = lane * m_laneSpace;

        Barrier newBarrier("barrier.obj", "barrier_Diffuse.png");
        newBarrier.setPosition(glm::vec3(laneOffset, barrierPos.y, player.getPosition().z + 100.0f));

        try {
            std::cout << "Spawning new barrier at position: " << newBarrier.getPosition().z << std::endl;
            m_barriers.push_back(newBarrier);
            std::cout << "New barrier spawned. Total barriers: " << m_barriers.size() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught while adding new barrier: " << e.what() << std::endl;
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

    for (auto& barrier : m_barriers)
    {
        barrier.draw(shader);
    }

}
