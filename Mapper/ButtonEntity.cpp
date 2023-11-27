#include "ButtonEntity.h"
#include "Program.h"
#include "SpriteComponent.h"

ButtonEntity::ButtonEntity(Program* program, std::string filename, const SDL_Rect& rect)
	:Entity(program)
{
	SpriteComponent* sc = new SpriteComponent(this, 150, rect);
	sc->SetTexture(mProgram->GetTexture(filename));
}