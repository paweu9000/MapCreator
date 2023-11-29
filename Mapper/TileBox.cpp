#include "TileBox.h"
#include "Program.h"
#include "SpriteComponent.h"
#include <string>
#include "Tile.h"

TileBox::TileBox(Program* program)
	:Entity(program)
{
	SpriteComponent* sc = new SpriteComponent(this, 150, SDL_Rect{ 1300, 50, 300, 800 });
	std::string fileName = "textures/tile_box.png";
	sc->SetTexture(mProgram->GetTexture(fileName));
}

void TileBox::AddTile(Tile* tile, int layer)
{
	switch (layer)
	{
	case 1:
		mLayer1Tiles.emplace_back(tile);
		break;
	case 2:
		mLayer2Tiles.emplace_back(tile);
		break;
	case 3:
		mLayer3Tiles.emplace_back(tile);
	default:
		break;
	}
}