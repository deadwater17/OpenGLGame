#include "World.h"

World::World(const GLchar* VertexSrc, const GLchar* FragmentSrc)
	: player(this)
	, camera(&player, &shader)	
	, keyboard(SDL_NUM_SCANCODES, 0)
	, playermodel("curuthers.obj")
	, shader(VertexSrc, FragmentSrc)

{ 
	enemyPos = glm::vec3 (3,0,-3);
	// Initialize the plane model
	plane = Model("flatPlane.obj");
	enemyModel = Model("cm.obj");
}

void World::render()
{
	glUseProgram(basic.getID());
	player.update();
	camera.update();

	drawing();
}

void World::handleInput(float dt) 
{
	player.userInput(keyboard, dt);
	//std::cout << "moving" << std::endl;
}

void World::drawing()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -5.0f, 0.0f)); // Adjust position if necessary
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	GLint modelLoc = glGetUniformLocation(basic.getID(), "u_Model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint projLoc = glGetUniformLocation(basic.getID(), "u_Projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));

	GLint viewLoc = glGetUniformLocation(basic.getID(), "u_View");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

	glBindVertexArray(const_cast<Model&>(plane).vao_id());
	glDrawArrays(GL_TRIANGLES, 0, plane.vertex_count());

	glm::mat4 enemyModelMatrix = glm::mat4(1.0f);
	enemyModelMatrix = glm::translate(enemyModelMatrix, enemyPos); // Adjust position as needed

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(enemyModelMatrix));

	glBindVertexArray(const_cast<Model&>(enemyModel).vao_id());
	glDrawArrays(GL_TRIANGLES, 0, enemyModel.vertex_count());

}

