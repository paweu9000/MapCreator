#include "Tile.h"
#include "SpriteComponent.h"

Tile::Tile(Program* program, const SDL_Rect& rect, int layer)
	:Entity(program)
	, mLayer(layer)
{
	SpriteComponent* sc = new SpriteComponent(this, 200, rect);
}
