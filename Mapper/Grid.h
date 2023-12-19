#pragma once
#include "Entity.h"
#include "GridTile.h"
#include <vector>

class Grid : public Entity
{
public:
	struct GridLayer
	{
		GridTile* l1tile;
		GridTile* l2tile;
		GridTile* l3tile;
	};
	Grid(class Program* program, int xPoint, int yPoint);
	void ChangeScale(float scale) { mScale = scale; }
	void LoadData();
	void Draw(int mouseX, int mouseY, int layer);
	void getGridData();
private:
	int mX;
	int mY;
	float mScale;
	std::vector<std::vector<GridLayer>> mTiles;
};