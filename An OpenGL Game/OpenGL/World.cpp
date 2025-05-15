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
	, uiShader()
    , mesh(std::make_unique<Mesh>(positions, sizeof(positions), colors, sizeof(colors)))
    , player("models/curuthers.obj", "models/Whiskers_diffuse.png")     // player model
    , road("models/ground.obj", "models/ground_Diffuse.png")        // road model and texture
    , barrier("models/barrier.obj", "models/barrier_Diffuse.png")   
    , camera()
{
	glm::vec3 roadPos = road.getPosition();     
    // spawns 4 roads ahead first
    for (int i = 0; i < 4; ++i) {
        road.setPosition(glm::vec3(0.0f, roadPos.y, i * m_tileLength));     // spawns with the same y axis
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

    lightManager.update(player.getPosition());      
    
}

void World::handleInput(float dt, const Uint8* keyboardState)
{   
	player.handleInput(keyboardState, dt);
}

void World::updateRoads()
{
    glm::vec3 playerPos = player.getPosition();     // gets the player position

    // Find the current farthest Z value
    float maxZ = 0.0f;
    for (const auto& road : m_roads)
    {
        if (road.getPosition().z > maxZ)
            maxZ = road.getPosition().z;
    }

    for (auto& road : m_roads)
    {
        if (road.getPosition().z + m_tileLength < playerPos.z)      
        {
            // Moves this road to be just after the farthest one
            road.setPosition(glm::vec3(0.0f, road.getPosition().y, maxZ + m_tileLength));
            maxZ = road.getPosition().z; // update maxZ
        }
    }
}

void World::updateBarrier(float dt)
{
	glm::vec3 barrierPos = barrier.getPosition();       

    for (size_t i = 0; i < m_barriers.size(); ++i) 
    {
        Barrier& b = m_barriers.at(i);      
        b.update(dt, player.getSpeed());        

    if (checkCollision(player, b)) 
        {
            if (!b.getHasCollided()) 
            {
                // decrease lives when player collides with barrier
                b.setHasCollided(true);
                takeDMG();
                
            }
        }
        else 
        {
            b.setHasCollided(false);

            if (!b.getHasBeenPassed() && b.getPosition().z < player.getPosition().z)
            {
                b.setHasBeenPassed(true);
                score.increaseScore(1);         // increases score when player passed the barrier's z axis
                std::cout << "Score increased! New score: " << score.getScore() << std::endl;
            }
        }
    }

    // Spawn new barriers every few seconds
    m_spawnTimer += dt;     
    if (m_spawnTimer >= m_spawnInterval)
    {
        m_spawnTimer = 0.0f;

        m_spawnInterval = (rand() % 5)+1;       // randomised spawn interval

        // randomly choose a lane: -1 (left), 0 (middle), 1 (right)
        int lane = (rand() % 3) - 1;
        float laneOffset = lane * m_laneSpace;

        Barrier newBarrier("models/barrier.obj", "models/barrier_Diffuse.png");
        newBarrier.setPosition(glm::vec3(laneOffset, barrierPos.y, player.getPosition().z + 100.0f));       // spawns barrier in one of the lanes

        try 
        {
            m_barriers.push_back(newBarrier);
        }
        catch (const std::exception& e) {
            std::cout << "Exception caught while adding new barrier: " << e.what() << std::endl;
        }
    }
}


void World::render()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    shader.use();

    lightManager.sendToShader(lightShader.getID());

    // Projection
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(120.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    GLint projLoc = glGetUniformLocation(shader.getID(), "u_Projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Camera
    glm::mat4 viewMatrix = camera.getViewMatrix();
    GLint viewLoc = glGetUniformLocation(shader.getID(), "u_View");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    mesh->draw(shader);

	player.draw(shader);        

    for(auto& road : m_roads)
	{
		road.draw(shader);
	}

    for (auto& barrier : m_barriers)
    {
        barrier.draw(shader);
    }

    // Disable depth and enable blending for UI
    glDisable(GL_DEPTH_TEST);

	uiShader.use();

    // Ortho projections
    glm::mat4 orthoProj = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(uiShader.getID(), "u_Projection"), 1, GL_FALSE, glm::value_ptr(orthoProj));

    // score matrix
    glm::mat4 identityView = glm::mat4(1.0f);
    identityView = glm::translate(identityView, glm::vec3(10, 10, 0)); // translated (position)
    identityView = glm::scale(identityView, glm::vec3(150, 25, 1)); // scale
    glUniformMatrix4fv(glGetUniformLocation(uiShader.getID(), "u_Model"), 1, GL_FALSE, glm::value_ptr(identityView));

    score.draw(uiShader);

    // lives matrix
    glm::mat4 livesMat = glm::mat4(1.0f);
    livesMat = glm::translate(livesMat, glm::vec3(650, 10, 0)); // translated (position)
    livesMat = glm::scale(livesMat, glm::vec3(150, 25, 1)); // scale 
    glUniformMatrix4fv(glGetUniformLocation(uiShader.getID(), "u_Model"), 1, GL_FALSE, glm::value_ptr(livesMat));

    lives.draw(uiShader);

    glEnable(GL_DEPTH_TEST);   

}

bool World::checkCollision(const Player& player, const Barrier& barrier)
{
    // Check if the barrier is close to the player's z-axis
    if (barrier.getPosition().z >= player.getPosition().z - 1.0f && barrier.getPosition().z <= player.getPosition().z + 1.0f) {
        // Check if the barrier is in the same lane as the player
        if (barrier.getPosition().x == player.getPosition().x) {
            return true;  // Collision is detected
        }
    }
    return false;  // No collision
}

void World::takeDMG()
{
    lives.decreaseLives(1);     // decreases lives by 1
}

