#include "World.h"

World::World(const GLchar* VertexSrc, const GLchar* FragmentSrc)
	: player(this)
	, keyboard(SDL_NUM_SCANCODES, 0)
	, playermodel("curuthers.obj")
	, basic(VertexSrc, FragmentSrc)
	, worldPos(0.0f, 0.0f, 0.0f)
{ }

void World::update()
{
	player.update();
	render();
}

void World::render()
{
	glUseProgram(basic.getID());

	player.display();
}
