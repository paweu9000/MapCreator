#pragma once
#include "Entity.h"
#include <vector>
#include <string>
#include "SDL.h"

class TileBox : public Entity
{
public:
	enum ActiveLayer
	{
		LAYER1, LAYER2, LAYER3
	};
	TileBox(class Program* program);
	SDL_Rect CalculateRect(int size);
	void AddTile(std::string tileName, int layer);
	void UpdateComponents() override;
	void SetActiveLayer(ActiveLayer layer) { mActiveLayer = layer; }
private:
	std::vector<class Tile*> mLayer1Tiles;
	std::vector<class Tile*> mLayer2Tiles;
	std::vector<class Tile*> mLayer3Tiles;
	ActiveLayer mActiveLayer;
};