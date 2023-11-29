#include "Tile.h"
#include "SpriteComponent.h"
#include "Program.h"

Tile::Tile(Program* program, const SDL_Rect rect, std::string fileName, int layer)
	:Entity(program)
	, mLayer(layer)
{
	SpriteComponent* sc = new SpriteComponent(this, 200+mLayer, rect);
	sc->SetTexture(program->GetTexture(fileName));
}
