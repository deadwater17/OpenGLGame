#include "World.h"

World::World(const GLchar* VertexSrc, const GLchar* FragmentSrc)
	: player(this)
	, camera(&player, this)	
	, keyboard(SDL_NUM_SCANCODES, 0)
	, playermodel("curuthers.obj")
	, basic(VertexSrc, FragmentSrc)

{ }

void World::render()
{
	glUseProgram(basic.getID());
	player.update();
	camera.update();
}

void World::handleInput(float dt) 
{
	player.userInput(keyboard, dt);
	//std::cout << "moving" << std::endl;
}