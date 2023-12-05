#pragma once
#include "Entity.h"
#include "GridTile.h"
#include <vector>

class Grid : public Entity
{
public:
	Grid(class Program* program, int xPoint, int yPoint);
	void ChangeScale(float scale) { mScale = scale; }
	void LoadData();
private:
	int mX;
	int mY;
	float mScale;
	std::vector<std::vector<GridTile*>> mTiles;
};