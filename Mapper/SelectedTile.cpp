#include "Program.h"
#include "SelectedTile.h"
#include "SpriteComponent.h"
#include <iostream>

SelectedTile::SelectedTile(Program* program, int x, int y, int layer, std::string tName)
	:Entity(program)
	, mX(x)
	, mY(y)
	, mLayer(layer)
	, mTextureName(tName)
{
}

void SelectedTile::UpdateComponents()
{
	for (auto component : mComponents)
	{
		SpriteComponent* sc = dynamic_cast<SpriteComponent*>(component);
		sc->SetRect({ mX, mY, 50, 50 });
	}
}