#include "GridTile.h"
#include "Program.h"
#include "Grid.h"
#include "SpriteComponent.h"

GridTile::GridTile(Program* program, SDL_Rect rect, std::string& path, int layer)
	:Entity(program)
	,mRect(rect)
	,mScale(1.0f)
	,mLayer(layer)
	,mTextureName("")
{
	if (!path.empty())
	{
		SpriteComponent* sc = new SpriteComponent(this, 200+mLayer, rect);
		sc->SetTexture(mProgram->GetTexture(path));
	}
}

bool GridTile::CheckBounds(int x, int y)
{
	if (x >= mRect.x && x <= mRect.x + mRect.w && y >= mRect.y && y <= mRect.h + mRect.y) return true;
	return false;
}

void GridTile::Draw(SDL_Texture* texture)
{
	if (mComponents.empty())
	{
		SpriteComponent* sc = new SpriteComponent(this, 200 + mLayer, mRect);
		sc->SetTexture(texture);
	}
	else
	{
		for (auto c : mComponents)
		{
			SpriteComponent* sc = dynamic_cast<SpriteComponent*>(c);
			sc->SetTexture(texture);
		}
	}
}