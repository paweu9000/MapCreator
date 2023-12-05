#include "GridTile.h"
#include "Program.h"
#include "Grid.h"
#include "SpriteComponent.h"

GridTile::GridTile(Program* program, SDL_Rect rect, std::string& path)
	:Entity(program)
	,mRect(rect)
	,mScale(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, 200, rect);
	sc->SetTexture(mProgram->GetTexture(path));
}