#pragma once
#include "Entity.h"
#include <vector>

class TileBox : public Entity
{
public:
	TileBox(class Program* program);
	void AddTile(class Tile*, int layer);
private:
	std::vector<class Tile*> mLayer1Tiles;
	std::vector<class Tile*> mLayer2Tiles;
	std::vector<class Tile*> mLayer3Tiles;
};