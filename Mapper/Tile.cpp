#include "Tile.h"
#include "SpriteComponent.h"
#include "Program.h"
#include <iostream>

Tile::Tile(Program* program, const SDL_Rect rect, std::string fileName, int layer)
	:Entity(program)
	, mLayer(layer)
	, mVisible(nullptr)
	, mTextureName(fileName)
	, mRect(rect)
{
	SpriteComponent* sc = new SpriteComponent(this, 200+mLayer, rect);
	sc->SetTexture(program->GetTexture(fileName));
}

void Tile::UpdateComponents()
{
	for (auto comp : mComponents)
	{
		auto* sc = dynamic_cast<SpriteComponent*>(comp);
		if (sc)
		{
			sc->setVisibility(mVisible);
		}
	}
	for (auto component : mComponents)
	{
		component->Update();
	}
}

bool Tile::IsInBounds(int x, int y)
{
	if (!mVisible) return false;
	if (x >= mRect.x && x <= mRect.x+mRect.w && y >= mRect.y && y <= mRect.h+mRect.y) return true;
	return false;
}
