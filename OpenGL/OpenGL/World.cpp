#include "World.h"

World::World(const GLchar* VertexSrc, const GLchar* FragmentSrc)
	: player(this)
	, keyboard(200)
	, playermodel("curuthers.obj")
	, basic(VertexSrc, FragmentSrc)
	, light(VertexSrc, FragmentSrc)

{ }

void World::render()
{
	glUseProgram(basic.getID());

	player.display();
}
