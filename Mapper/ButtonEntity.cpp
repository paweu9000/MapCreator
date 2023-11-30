#include "ButtonEntity.h"
#include "Program.h"
#include "SpriteComponent.h"

ButtonEntity::ButtonEntity(Program* program, std::string filename, const SDL_Rect& rect)
	:Entity(program)
	,mRect(rect)
{
	SpriteComponent* sc = new SpriteComponent(this, 150, rect);
	sc->SetTexture(mProgram->GetTexture(filename));
}

void ButtonEntity::ProcessMouseInput(int x, int y)
{
	if (x >= mRect.x and x <= mRect.x + mRect.w and 
		y >= mRect.y and y <= mRect.y + mRect.h)
	{
		ExecuteAction();
	}
}