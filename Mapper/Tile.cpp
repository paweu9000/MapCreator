#include "Tile.h"
#include "SpriteComponent.h"
#include "Program.h"

Tile::Tile(Program* program, const SDL_Rect rect, std::string fileName, int layer)
	:Entity(program)
	, mLayer(layer)
	, mVisible(nullptr)
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
