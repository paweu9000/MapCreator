#include "TileBox.h"
#include "Program.h"
#include "SpriteComponent.h"
#include "Tile.h"

TileBox::TileBox(Program* program)
	:Entity(program)
{
	SpriteComponent* sc = new SpriteComponent(this, 150, SDL_Rect{ 1300, 50, 300, 800 });
	std::string fileName = "textures/tile_box.png";
	sc->SetTexture(mProgram->GetTexture(fileName));
}

void TileBox::AddTile(std::string tileName, int layer)
{
	Tile* tile;
	switch (layer)
	{
	case 1:
		tile = new Tile(this->getProgram(), CalculateRect(mLayer1Tiles.size()), tileName, layer);
		mLayer1Tiles.emplace_back(tile);
		break;
	case 2:
		tile = new Tile(this->getProgram(), CalculateRect(mLayer2Tiles.size()), tileName, layer);
		mLayer2Tiles.emplace_back(tile);
		break;
	case 3:
		tile = new Tile(this->getProgram(), CalculateRect(mLayer3Tiles.size()), tileName, layer);
		mLayer3Tiles.emplace_back(tile);
		break;
	default:
		break;
	}
}

SDL_Rect TileBox::CalculateRect(int size)
{
	int row = size / 3;
	int column = size % 3;

	SDL_Rect rect;
	rect.x = 1320 + column * 60;
	rect.y = 70 + row * 60;
	rect.w = 50;
	rect.h = 50;

	return rect;
}