#include "TileBox.h"
#include "Program.h"
#include "SpriteComponent.h"
#include "Tile.h"
#include <iostream>

TileBox::TileBox(Program* program)
	:Entity(program)
	,mActiveLayer(LAYER1)
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
		tile->setVisibility(this->mActiveLayer == LAYER1);
		mLayer1Tiles.emplace_back(tile);
		break;
	case 2:
		tile = new Tile(this->getProgram(), CalculateRect(mLayer2Tiles.size()), tileName, layer);
		tile->setVisibility(this->mActiveLayer == LAYER2);
		mLayer2Tiles.emplace_back(tile);
		break;
	case 3:
		tile = new Tile(this->getProgram(), CalculateRect(mLayer3Tiles.size()), tileName, layer);
		tile->setVisibility(this->mActiveLayer == LAYER3);
		mLayer3Tiles.emplace_back(tile);
		break;
	default:
		break;
	}
}

void TileBox::UpdateComponents()
{
	for (auto t1 : mLayer1Tiles)
	{
		t1->setVisibility(mActiveLayer == LAYER1);
	}
	for (auto t2 : mLayer2Tiles)
	{
		t2->setVisibility(mActiveLayer == LAYER2);
	}
	for (auto t3 : mLayer3Tiles)
	{
		t3->setVisibility(mActiveLayer == LAYER3);
	}
	for (auto component : mComponents)
	{
		component->Update();
	}
}

SDL_Rect TileBox::CalculateRect(int size)
{
	int row = size / 4;
	int column = size % 4;

	SDL_Rect rect;
	rect.x = 1320 + column * 60;
	rect.y = 70 + row * 60;
	rect.w = 50;
	rect.h = 50;

	return rect;
}