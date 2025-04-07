#include "World.h"

World::World(const GLchar* VertexSrc, const GLchar* FragmentSrc)
	: player(this)
	, keyboard(SDL_NUM_SCANCODES, 0)
	, playermodel("curuthers.obj")
	, basic(VertexSrc, FragmentSrc)
	, light(VertexSrc, FragmentSrc)

{ }

void World::render()
{
	glUseProgram(basic.getID());

	player.display();
	player.update();
}

void World::handleInput() 
{
	player.userInput(keyboard);
	//std::cout << "moving" << std::endl;
}